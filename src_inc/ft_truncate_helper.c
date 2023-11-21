/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:32 by iengels           #+#    #+#             */
/*   Updated: 2023/04/27 00:08:34 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize_truncate(int *i, unsigned int *q, unsigned int *j)
{
	*i = -1;
	*q = 0;
	*j = 0;
}

int	ft_askopen_qstatus(int q, int m_q[3], char s)
{
	if ((q == 0 && (s == '\'' || s == '\"')) && ((m_q[0] != 0 && s == '\"')
				|| (m_q[1] != 0 && s == '\'')))
		return (1);
	return (0);
}

void	ft_change_q_status(unsigned int *q, int m_q[3], char s, int p)
{
	if (p == 0)
	{
		m_q[s % 2]--;
		*q = 1 + (s % 2);
	}
	if (p == 1)
	{
		m_q[s % 2]--;
		*q = 0;
	}
}

void	ft_set_to_zero(unsigned int *i, unsigned int *q, unsigned int *j)
{
	*i = 0;
	*q = 0;
	*j = 0;
}

int	ft_get_qvariable(char *s1, unsigned int **d, t_var *v)
{
	char	*value;
	int		p;

	(void)v;
	p = -1;
	value = ft_itoa(g_status);
	while (value[++p])
		s1[(**d)++] = value[p];
	free(value);
	return (1);
}
