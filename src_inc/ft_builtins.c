/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:05:09 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:18:52 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_env(t_dlist *export, int i)
{
	char	*s1;
	char	*s2;

	while (export)
	{
		s1 = ft_strjoin(export->str, "\n");
		s2 = ft_strjoin("declare -x ", s1);
		if (i != 1 && ft_strchr(export->str, '=') != 0)
			ft_putstr_fd(s1, 1);
		else if (i == 1)
			ft_putstr_fd(s2, 1);
		free(s1);
		free(s2);
		s1 = NULL;
		s2 = NULL;
		export = export->next;
	}
	return (1);
}

void	ft_do_export2(t_dlist *expor, t_tlist *lis, int j)
{
	t_dlist	*export;

	export = expor;
	free(export->str);
	export->str = NULL;
	export->str = ft_strdup(lis->flargs[j]);
}

int	ft_do_export(t_dlist **expor, t_tlist *lis)
{
	int		j;
	t_dlist	*export;

	export = *expor;
	j = 0;
	while (lis->flargs[j])
	{
		while (export != NULL)
		{
			if (ft_strccmp(export->str, lis->flargs[j], '=') == 0)
			{
				ft_do_export2(export, lis, j);
				return (1);
			}
			export = (export)->next;
		}
		ft_add_dlist_back(&*expor, lis->flargs[j], 0);
		j++;
	}
	return (1);
}

int	ft_do_unset(t_dlist **expor, t_tlist *lis)
{
	int		i;
	t_dlist	*export;
	char	*str;

	export = *expor;
	i = ft_strlen(lis->flargs[0]) + 1;
	while (export != NULL)
	{
		str = ft_strdup(lis->flargs[0]);
		if (ft_help_unset(&export, str, i - 1) == 0)
			break ;
		free(str);
		export = (export)->next;
	}
	if (export != NULL)
	{
		free(export->str);
		free(export);
	}
	return (1);
}

int	ft_build_in(t_tlist **l, t_var *vars, t_dlist **export)
{
	t_tlist	*lis;

	lis = *l;
	if (ft_buildins2(lis, &*export))
		return (1);
	if (lis->command == NULL && lis->doc != NULL && vars->t == 0)
	{
		return (1);
	}
	if (lis->doc != NULL && vars->t == 0)
	{
		ft_putstr_fd(lis->doc, 1);
		return (1);
	}
	if (lis->prev != NULL && lis->prev->op != NULL && ft_strcmp(lis->prev->op,
			"<") == 0)
	{
		ft_replace2(lis->prev, vars);
		return (0);
	}
	return (0);
}
