/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fastgirl <fastgirl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:06 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 20:06:15 by fastgirl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**ft_get_path(t_dlist *export)
{
	char	*env;
	char	**new;
	t_dlist	*expor;

	expor = export;
	new = NULL;
	while (export)
	{
		if (ft_strncmp(export->str, "PATH", 4) == 0)
		{
			env = export->str;
			break ;
		}
		export = export->next;
	}
	if (export != NULL)
		new = ft_split(env, ':');
	export = expor;
	return (new);
}

int	ft_check_operator(t_tlist *lis, t_var *vars)
{
	if (lis->command != NULL && ft_strcmp(lis->command, "exit") == 0)
	{
		ft_putstr_fd("exit\n", 1);
		if (lis->flargs != NULL && lis->flargs[0] != NULL)
			ft_free_and_exit(vars, ft_atoi(lis->flargs[0]));
		else
			ft_free_and_exit(vars, 0);
	}
	if (lis->op != NULL)
	{
		if (ft_strcmp(lis->op, "<") == 0)
			return (4);
	}
	if (lis->prev == NULL)
		return (0);
	if (lis->prev->op == NULL)
		return (0);
	if (ft_strcmp(lis->prev->op, ">") == 0)
		return (ft_replace(lis->command, vars->in, NULL));
	else if (ft_strcmp(lis->prev->op, ">>") == 0)
		return (ft_add(lis, vars));
	return (0);
}

void	close_and_wait(t_var *vars)
{
	if (vars->in != 0)
		close(vars->in);
	while (vars->j < vars->count_token)
		waitpid(vars->pid[vars->j++], &vars->wstatus, 0);
	if (WIFEXITED(vars->wstatus))
		g_status = WEXITSTATUS(vars->wstatus);
}

int	special_case(t_tlist *lis, t_var *vars, t_dlist **export)
{
	(void)vars;
	if (lis->command != NULL && ft_strcmp(lis->command, "cd") == 0)
		return (ft_change_dir(lis, &*export));
	else if (lis->command != NULL && lis->flargs != NULL
			&& ft_strcmp(lis->command, "export") == 0)
		return (ft_do_export(&*export, lis));
	else if (lis->command != NULL && ft_strcmp(lis->command, "unset") == 0)
		return (ft_do_unset(&*export, lis));
	return (0);
}

int	ft_input_check(t_tlist *lis, t_var *vars, t_dlist **export)
{
	int	i;

	input_check_init(vars);
	i = 0;
	vars->t = 0;
	while (i < vars->count_token)
	{
		vars->pid[i] = 0;
		vars->op_check = ft_check_operator(lis, vars);
		if (ft_input_helper(&lis, &vars, &*export, i))
			return (1);
		i++;
	}
	close_and_wait(vars);
	free(vars->pid);
	return (1);
}
