/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:29:27 by iengels           #+#    #+#             */
/*   Updated: 2022/10/23 12:42:29 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_index(const char *str, const char *set)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	while (str[a])
	{
		b = 0;
		while (str[a] != set[b])
		{
			if (str[a] != set[b] && set[b] == '\0')
				return (a);
			b++;
		}
		a++;
	}
	return (a);
}

static int	ft_revindex(const char *str, const char *set)
{
	unsigned int	a;
	unsigned int	b;

	a = ft_strlen(str);
	while (a > 0)
	{
		b = 0;
		while (str[a] != set[b])
		{
			if (str[a] != set[b] && set[b] == '\0')
				return (a);
			b++;
		}
		a--;
	}
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*str;

	start = ft_index(s1, set);
	end = ft_revindex(s1, set);
	end = end + 1 - start;
	str = ft_substr(s1, start, end);
	return (str);
}
