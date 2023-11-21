/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:05:06 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:19:14 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_access(t_var *vars, char *str, char *path)
{
	int		i;
	char	*tmp1;

	i = 0;
	while (vars->path && vars->path[i])
	{
		if (path)
			tmp1 = ft_strjoin_3(path, "/", str);
		else
			tmp1 = ft_strjoin_3(vars->path[i], "/", str);
		if (access(tmp1, F_OK) == 0)
		{
			free(tmp1);
			return (i);
		}
		i++;
		free(tmp1);
		if (path)
			break ;
	}
	return (-1);
}

char	**ft_make_argv(t_tlist *lis, t_var *v)
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
	k = -1;
	argv[i++] = ft_strdup(lis->command);
	if (lis->flargs != NULL)
	{
		while (lis->flargs[++k])
			argv[i++] = ft_strdup(lis->flargs[k]);
	}
	argv[i] = NULL;
	return (argv);
}

void	ft_invalid_command(char *str, char ***avg, t_var *vars)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	free_stuff((*avg));
	ft_free_and_exit(vars, 127);
}

void	ft_execve(t_tlist *lis, t_var *vars)
{
	int		k;
	char	**avg;

	avg = ft_make_argv(lis, vars);
	if (lis->command == NULL)
		k = -1;
	else
		k = ft_check_access(vars, lis->command, lis->path);
	if (ft_check_command(lis->command, k, lis) == 1)
		ft_invalid_command(lis->command, &avg, vars);
	else if (lis->command[0] == '.' && lis->command[1] == '/')
		execve(ft_strjoin("./", lis->command), avg, vars->env);
	else if (lis->command[1] != '\0')
	{
		if (lis->path == NULL)
			execve(ft_strjoin(ft_strjoin(vars->path[k], "/"), lis->command),
					avg,
					vars->env);
		else
			execve(ft_strjoin(ft_strjoin(lis->path, "/"), lis->command), avg,
					vars->env);
	}
	if (lis->command != NULL)
		ft_putstr_fd(lis->command, 2);
	ft_free_and_exit(vars, 127);
}

void	ft_child(t_tlist *lis, t_var *vars, int i, t_dlist **export)
{
	pipe(vars->fd);
	vars->pid[i] = fork();
	if (vars->pid[i] == 0)
	{
		if (i != 0)
			dup2(vars->in, STDIN_FILENO);
		if (i != vars->count_token - 1)
			dup2(vars->fd[1], STDOUT_FILENO);
		close(vars->fd[0]);
		close(vars->fd[1]);
		if (ft_build_in(&lis, vars, &*export) == 0)
			ft_execve(lis, vars);
		else
			vars->j++;
		ft_free_and_exit(vars, 0);
	}
	if (lis->command != NULL && ft_strcmp(lis->command, "cat") == 0
		&& lis->flargs == NULL)
		dup2(STDIN_FILENO, vars->fd[0]);
	else
		vars->in = dup(vars->fd[0]);
	close(vars->fd[0]);
	close(vars->fd[1]);
}
