/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:27 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 19:47:12 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_token_loop(char *s, int *q, unsigned int *i, int **m_q)
{
	(*m_q)[2] = 0;
	while (s[*i] && (ft_space_check(s[*i], *q) == 1) && ft_is_operator(&s[*i],
			*q) == 0)
	{
		if ((*q == 0 && (s[*i] == '\'' || s[*i] == '\"')) && (((*m_q)[0] != 0
				&& s[*i] == '\"') || ((*m_q)[1] != 0 && s[*i] == '\'')))
		{
			(*m_q)[s[*i] % 2]--;
			*q = 1 + (s[*i] % 2);
		}
		else if ((*q == 2 && s[*i] == '\'') || (s[*i] == '\"' && *q == 1))
		{
			(*m_q)[2] = *q;
			*q = 0;
		}
		(*i)++;
	}
}

int	ft_search_for_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
