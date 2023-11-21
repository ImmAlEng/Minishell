/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:12:32 by iengels           #+#    #+#             */
/*   Updated: 2023/04/25 01:44:18 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "ft_strlen.c"
// #include "ft_substr.c"
// #include <stdio.h>

static void	*ft_free(char **new, unsigned int a)
{
	while (a)
	{
		free(new[a]);
		a--;
	}
	free(new);
	return (NULL);
}

static unsigned int	ft_wordcount(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	ft_endcount(char const *s, unsigned int end, char c)
{
	while (s[end] && (char)s[end] != c)
		end++;
	return (end);
}

static int	ft_startcount(char const *s, unsigned int start, char c)
{
	while (s[start] && (char)s[start] == c)
		start++;
	return (start);
}

char	**ft_split(char const *s, char c)
{
	char			**new;
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	unsigned int	end;

	j = ft_wordcount((char *)s, c);
	i = 0;
	if (!s)
		return (0);
	new = malloc(sizeof(char *) * (j + 1));
	if (!new)
		return (NULL);
	end = 0;
	while (j-- && s[0] != '\0')
	{
		start = ft_startcount(s, end, c);
		end = ft_endcount(s, start, c);
		new[i] = ft_substr(s, start, end - start);
		if (!new[i])
			return (ft_free(new, i));
		i++;
	}
	new[i] = NULL;
	return (new);
}

// int	main(void)
// {
// 	char **fucker;
// 	fucker = ft_split("      split       this for   me  !       ", ' ');
// 	while (*fucker)
// 	{
// 		printf(":%s:\n", *fucker);
// 		fucker++;
// 	}
// }