/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:03 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 19:22:11 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_freetoken_back(t_tlist *lis)
{
	int		i;
	t_tlist	*tmp;

	if (lis->prev != NULL)
		lis = lis->prev;
	while (lis->prev != NULL)
	{
		tmp = lis;
		tmp = tmp->prev;
		free(lis->op);
		free(lis->command);
		i = 0;
		while (lis->flargs != NULL && lis->flargs[i] != NULL)
			free(lis->flargs[i++]);
		free(lis);
		lis = tmp;
	}
	return (NULL);
}

void	free_stuff(char **avg)
{
	unsigned int	i;

	i = 0;
	if (avg != NULL)
	{
		while (avg[i] != NULL)
		{
			free(avg[i]);
			avg[i] = NULL;
			i++;
		}
		free(avg);
		avg = NULL;
	}
}

void	ft_free_prompt(t_var *v)
{
	if (v->minishell != NULL)
	{
		free(v->minishell);
		v->minishell = NULL;
	}
}

void	ft_free_child(t_var *vars, t_dlist **export)
{
	ft_free_all(*export);
	ft_freetoken(vars->head);
	free(vars);
	rl_clear_history();
}

void	ft_free_and_exit(t_var *v, int exit_code)
{
	ft_free_prompt(v);
	ft_freelist(v->exp);
	if (v->head != NULL)
		ft_freetoken(v->head);
	free_stuff(v->path);
	if (v->pid != NULL)
		free(v->pid);
	free(v);
	if (exit_code == 127)
			ft_putstr_fd(": command not found\n", 2);
	rl_clear_history();
	exit(exit_code);
}
