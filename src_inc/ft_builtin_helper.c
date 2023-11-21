/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:15 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 22:01:58 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_buildins2(t_tlist *lis, t_dlist **export)
{
	if (lis->command != NULL && ft_strcmp(lis->command, "pwd") == 0)
		return (ft_getdir());
	if ((lis->command != NULL && ft_strcmp(lis->command, "echo") == 0))
		return (ft_do_echo(lis));
	if (lis->command != NULL && lis->flargs == NULL && ft_strcmp(lis->command,
			"export") == 0)
		return (ft_print_env(*export, 1));
	if (lis->command != NULL && ft_strcmp(lis->command, "env") == 0)
		return (ft_print_env(*export, 0));
	return (0);
}

int	ft_help_unset(t_dlist **expor, char *str, int i)
{
	(void)i;
	if (ft_strccmp((*expor)->str, str, '=') == 0)
	{
		if ((*expor)->prev != NULL)
			(*expor)->prev->next = (*expor)->next;
		if ((*expor)->next != NULL)
			(*expor)->next->prev = (*expor)->prev;
		free(str);
		return (0);
	}
	else
		return (1);
}

int	ft_add2_helper(t_tlist *lis, t_var *v, char **str, char *input)
{
	char	*tmp;
	char	*tmp2;

	if (input == NULL)
		return (ft_heredoc_error(v, str));
	else
	{
		if (input[0] == '\0')
			ft_putchar_fd('\n', 1);
		tmp2 = ft_strdup(*str);
		if (ft_strcmp(input, lis->next->command) == 0)
		{
			free(tmp2);
			return (1);
		}
		free(*str);
		*str = NULL;
		tmp = ft_strjoin(input, "\n");
		*str = ft_strjoin(tmp2, tmp);
		free(tmp);
	}
	free(tmp2);
	return (0);
}

char	*ft_replace_helper(int in, char *str)
{
	char	*s;
	char	*tmp;

	while (1)
	{
		s = NULL;
		s = get_next_line(in);
		if (s == NULL)
			break ;
		tmp = ft_strdup(str);
		str = ft_strjoin(tmp, s);
		free(tmp);
		tmp = NULL;
		free(s);
	}
	return (str);
}

int	ft_input_helper(t_tlist **lis, t_var **vars, t_dlist **export, int i)
{
	if ((*vars)->op_check == 5)
	{
		free((*vars)->pid);
		return (1);
	}
	if ((*vars)->op_check == 4)
	{
		(*lis) = (*lis)->next;
		(*vars)->count_token--;
	}
	if (((*vars)->op_check == 4 || (*vars)->op_check == 0)
		&& !(special_case((*lis), (*vars), &*export)))
		ft_child((*lis), (*vars), i, &*export);
	if ((*lis)->doc != NULL && (*lis)->command != NULL && (*vars)->t == 0)
		(*vars)->t = 1;
	else
	{
		(*lis) = (*lis)->next;
		(*vars)->t = 0;
	}
	return (0);
}
