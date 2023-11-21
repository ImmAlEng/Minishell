/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:21 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:19:30 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_command(char *str, int k, t_tlist *lis)
{
	if (!str)
		return (1);
	if (lis->path != NULL)
		return (0);
	if (str[0] != '\0' && str[1] != '\0')
	{
		if (k == -1 && str[0] != '.' && str[1] != '/')
			return (1);
	}
	return (0);
}

void	ft_free_all(t_dlist *exp)
{
	ft_freelist(exp);
	exp = NULL;
	ft_putstr_fd("exit\n", 1);
}

void	ft_freetoken2(t_tlist *l)
{
	if (l->next != NULL)
		ft_freetoken(l->next);
	if (l->op != NULL)
		free(l->op);
	if (l->command != NULL)
		free(l->command);
	if (l->path != NULL)
		free(l->path);
	if (l->env != NULL)
		free(l->env);
	if (l->doc != NULL)
		free(l->doc);
}

int	ft_count_token(t_tlist *lis)
{
	int	i;

	i = 0;
	while (lis)
	{
		if (lis->doc != NULL && lis->command != NULL)
			i++;
		lis = lis->next;
		i++;
	}
	return (i);
}

int	ft_is_variable(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=' && s[i + 1] != '\0')
			return (0);
		i++;
	}
	return (1);
}
