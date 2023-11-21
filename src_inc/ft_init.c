/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:05:11 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 17:51:06 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getdir(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 2000);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (1);
}

void	ft_free_innerloop(t_var *v, t_tlist **lis)
{
	if (v->id == 1)
		*lis = ft_freetoken(v->head);
	free(v->input);
	v->input = NULL;
}

void	ft_vars_initiate(t_var *v, char **env, t_dlist **export)
{
	g_status = 0;
	v->wstatus = 0;
	v->id = 1;
	v->pid = NULL;
	v->env = env;
	v->true = 1;
	*export = ft_export_list(v);
	v->exp = *export;
}

void	ft_copy_int_array(int (*dest)[3], int src[3], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		(*dest)[i] = src[i];
		i++;
	}
}

int	input_check_init(t_var *vars)
{
	vars->pid = malloc(sizeof(pid_t) * vars->count_token);
	if (!vars->pid)
		ft_free_and_exit(vars, 1);
	vars->in = 0;
	vars->j = 0;
	return (1);
}
