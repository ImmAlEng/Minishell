/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:26 by iengels           #+#    #+#             */
/*   Updated: 2023/04/25 01:44:06 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*ft_get_home_path(t_tlist *t)
{
	char	*home;
	char	*tmp;

	home = NULL;
	if (t->env != NULL)
		home = getenv("HOME");
	if (home == NULL)
	{
		tmp = getcwd(NULL, 0);
		home = ft_strjoin(tmp, "/");
		free(tmp);
	}
	return (home);
}
*/

void	ft_relativ_path(t_tlist *t)
{
	char	*tmp;
	char	*tmp2;
	char	*home;

	if (t->path[0] == '~' && t->path[1] == '/')
	{
		home = getenv("HOME");
		tmp = ft_strjoin(home, &t->path[1]);
		free(t->path);
		t->path = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		tmp = getcwd(NULL, 0);
		tmp2 = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = ft_strjoin(tmp2, t->path);
		free(tmp2);
		free(t->path);
		t->path = ft_strdup(tmp);
		free(tmp);
	}
}

int	ft_check_dot_slash(char *s)
{
	unsigned int	i;

	i = ft_strlen(s) - 1;
	if (i > 1)
		if (s[i - 2] == '/' && s[i - 1] == '.')
			return (1);
	return (0);
}

void	ft_make_exec_dotslash(t_tlist *t)
{
	char	*tmp;

	tmp = ft_strjoin("./", t->command);
	free(t->command);
	t->command = ft_strdup(tmp);
	free(tmp);
}

void	ft_divide_path_and_str(t_tlist *t)
{
	int		i;
	char	*tmp;

	i = ft_strlen(t->command) - 1;
	while (t->command[i] != '/')
		i--;
	tmp = ft_strdup(t->command);
	free(t->command);
	t->command = ft_strdup(&tmp[i + 1]);
	t->path = ft_substr(tmp, 0, i + 1);
	free(tmp);
	if (t->path[0] != '/')
		ft_relativ_path(t);
	if (ft_check_dot_slash(t->path))
		ft_make_exec_dotslash(t);
}

void	ft_get_command_path(t_tlist *t)
{
	while (t != NULL)
	{
		if (t->command != NULL)
		{
			if (ft_search_for_slash(t->command))
				ft_divide_path_and_str(t);
		}
		t = t->next;
	}
}
