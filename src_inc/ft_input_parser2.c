/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:29 by iengels           #+#    #+#             */
/*   Updated: 2023/04/24 22:07:12 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_space_check(char c, int q)
{
	if (q != 0)
		return (1);
	if (c == 32)
		return (0);
	return (1);
}

int	ft_check_open_q(char *s)
{
	unsigned int	i;
	unsigned int	q;

	i = 0;
	q = 0;
	while (s[i])
	{
		while (ft_space_check(s[i], 0) == 0)
			i++;
		while (s[i] && (ft_space_check(s[i], q) == 1))
		{
			if (q == 0 && (s[i] == '\'' || s[i] == '\"'))
				q = 1 + (s[i] % 2);
			else if ((q == 2 && s[i] == '\'') || (s[i] == '\"' && q == 1))
				q = 0;
			i++;
		}
	}
	if (q != 0)
		return (1);
	return (0);
}

int	ft_op_only(t_tlist *lis)
{
	if (lis->command == NULL && lis->flargs == NULL && lis->doc == NULL
		&& lis->next == NULL)
		return (1);
	return (0);
}

int	ft_incomplete(t_tlist *lis, t_var *v)
{
	if (ft_op_only(lis))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token |\n", 2);
		return (0);
	}
	while (lis->next != NULL)
		lis = lis->next;
	if ((lis->op != NULL) && lis->op[0] == '|')
		v->id = 2;
	else if (lis->op == NULL)
		v->id = 1;
	return (0);
}

void	ft_free_prompt1(char **p)
{
	unsigned int	i;

	i = 5;
	while (i--)
		free(p[i]);
	free(p);
}
