/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:06:44 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 19:54:12 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_echo(t_tlist *lis)
{
	int	i;

	i = 0;
	if (lis->flargs == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if (ft_strcmp(lis->flargs[0], "-n") == 0)
		i = 1;
	while ((lis->flargs[i] != NULL) && lis->flargs[i + 1] != NULL)
	{
		ft_putstr_fd(lis->flargs[i++], 1);
		ft_putchar_fd(' ', 1);
	}
	if (lis->flargs[i] != NULL)
		ft_putstr_fd(lis->flargs[i], 1);
	if (ft_strcmp(lis->flargs[0], "-n") != 0)
		ft_putchar_fd('\n', 1);
	return (1);
}

int	ft_change_dir(t_tlist *lis, t_dlist **export)
{
	t_dlist	*expor;

	expor = *export;
	if (lis->flargs != NULL)
	{	
		if (chdir(lis->flargs[0]) == -1)
			ft_putstr_fd("cd: No such file or directory\n", 1);
	}
	else
	{
		while (*export)
		{
			if (ft_strncmp((*export)->str, "HOME", 4) == 0)
			{
				chdir(getenv("HOME"));
				break ;
			}
			*export = (*export)->next;
		}
		if (*export == NULL)
			ft_putstr_fd("cd: HOME not set\n", 1);
		*export = expor;
	}
	return (1);
}

char	**ft_do_avg(t_tlist *lis, t_var *v)
{
	int		i;
	int		k;
	char	**argv;

	i = 0;
	k = 0;
	argv = NULL;
	if (lis->flargs != NULL)
	{
		while (lis->flargs[k])
			k++;
	}
	argv = malloc(sizeof(char *) * (k + 2));
	if (!argv)
		ft_free_and_exit(v, 1);
	k = 0;
	if (lis->flargs != NULL)
	{
		while (lis->flargs[k])
			argv[i++] = lis->flargs[k++];
	}
	argv[i++] = lis->command;
	argv[i] = NULL;
	return (argv);
}

char	**ft_do_avg2(t_tlist *lis, t_var *v)
{
	int		i;
	int		k;
	char	**argv;

	i = 0;
	k = 0;
	argv = NULL;
	if (lis->flargs != NULL)
	{
		while (lis->flargs[k])
			k++;
	}
	argv = malloc(sizeof(char *) * (k + 3));
	if (!argv)
		ft_free_and_exit(v, 1);
	k = 0;
	argv[i++] = lis->command;
	if (lis->flargs != NULL)
	{
		while (lis->flargs[k])
			argv[i++] = lis->flargs[k++];
	}
	argv[i++] = lis->next->command;
	argv[i] = NULL;
	return (argv);
}

t_dlist	*ft_export_list(t_var *v)
{
	int		i;
	t_dlist	*export;

	i = 0;
	export = ft_create_dlist(v->env[i++], 0);
	while (v->env[i])
		ft_add_dlist_back(&export, v->env[i++], 0);
	return (export);
}
