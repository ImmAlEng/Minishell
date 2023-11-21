/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:31 by iengels           #+#    #+#             */
/*   Updated: 2023/04/24 22:07:32 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_last_occ_char(char *s)
{
	int		i;
	char	q;

	i = 0;
	if (s[0] == '\0')
		return (1);
	q = s[i++];
	while (s[i] != '\0')
	{
		if (s[i] == q)
			return (0);
		i++;
	}
	return (1);
}

int	ft_open_state(char *s, int st, int (**q)[3])
{
	int	i;

	i = 0;
	if (st == 0 && (s[i] == '\'' || s[i] == '\"'))
	{
		(**q)[s[i] % 2]++;
		if (ft_last_occ_char(s + i) == 1)
			return (0);
		return (1);
	}
	return (0);
}

int	ft_close_state(char c, int st, int (**q)[3])
{
	if ((c == '\'' && st == 2) || (c == '\"' && st == 1))
	{
		(**q)[c % 2]++;
		return (1);
	}
	return (0);
}

void	ft_last_quote(char *s, int (*q)[3])
{
	int	i;
	int	st;

	st = 0;
	i = 0;
	(*q)[0] = 0;
	(*q)[1] = 0;
	(*q)[2] = 0;
	while (s[i] != '\0')
	{
		if (ft_open_state(s + i, st, &q))
			st = 1 + s[i] % 2;
		else if (ft_close_state(s[i], st, &q))
			st = 0;
		i++;
	}
	(*q)[0] = (*q)[0] - (*q)[0] % 2;
	(*q)[1] = (*q)[1] - (*q)[1] % 2;
}
