/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:19:56 by iengels           #+#    #+#             */
/*   Updated: 2022/10/19 18:45:05 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	if (!src && !dest)
		return (NULL);
	if ((dest == src) || n == 0)
		return (dest);
	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	while (n--)
		p_dest[n] = p_src[n];
	return (dest);
}
