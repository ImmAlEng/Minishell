/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:13:59 by iengels           #+#    #+#             */
/*   Updated: 2022/10/19 22:22:38 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	ch;
	size_t			i;

	string = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (string[i] == ch)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
