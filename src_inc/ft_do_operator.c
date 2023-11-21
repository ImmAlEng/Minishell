/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:23 by iengels           #+#    #+#             */
/*   Updated: 2023/04/27 23:02:19 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add2(t_tlist *lis, t_var *v)
{
	char	*input;
	char	*str;
	char	*prompt;

	str = ft_strdup("");
	while (1)
	{
		signal(SIGINT, ft_sigint);
		prompt = ft_get_prompt(3, 0, 0, v);
		input = readline(prompt);
		free(prompt);
		if (g_status == 130)
			break ;
		if (ft_add2_helper(lis, v, &str, input) == 1)
			break ;
	}
	if (g_status == 130)
		free(input);
	return (str);
}

char	*ft_do_path(t_tlist *lis, t_var *v, int k)
{
	if (lis->path == NULL)
		return (ft_strjoin(v->path[k], "/"));
	else
		return (ft_strjoin(lis->path, "/"));
}

int	ft_replace2(t_tlist *lis, t_var *v)
{
	int		k;
	char	**avg;
	char	*path;

	if (lis->command == NULL)
	{
		avg = ft_do_avg(lis->next, v);
		k = ft_check_access(v, lis->next->flargs[0], lis->path);
		path = ft_do_path(lis, v, k);
	}
	else
	{
		avg = ft_do_avg2(lis, v);
		k = ft_check_access(v, lis->command, lis->path);
		path = ft_do_path(lis, v, k);
	}
	execve(ft_strjoin(path, avg[0]), avg, v->env);
	return (3);
}

int	ft_add(t_tlist *lis, t_var *vars)
{
	int		fd;
	int		i;
	char	*s;
	char	*str;

	s = NULL;
	str = "";
	i = access(lis->command, F_OK);
	if (i != 0)
		fd = open(lis->command, O_RDWR | O_CREAT | O_APPEND, 00777);
	else
		i = access(lis->command, W_OK);
	fd = open(lis->command, O_RDWR | O_APPEND);
	while (1)
	{
		s = get_next_line(vars->in);
		if (s == NULL)
			break ;
		str = ft_strjoin(str, s);
		free(s);
	}
	write(fd, str, ft_strlen(str));
	close(fd);
	free(str);
	return (1);
}

int	ft_replace(char *command, int in, char *str)
{
	int	fd;
	int	i;

	if (str == NULL)
		str = "";
	i = access(command, F_OK);
	if (i != 0)
		fd = open(command, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	else
		i = access(command, W_OK);
	fd = open(command, O_WRONLY | O_TRUNC);
	if (in != 0)
		str = ft_replace_helper(in, str);
	write(fd, str, ft_strlen(str));
	close(fd);
	free(str);
	return (1);
}
