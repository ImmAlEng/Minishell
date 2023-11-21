/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:43:24 by iengels           #+#    #+#             */
/*   Updated: 2022/10/20 14:24:46 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*string;

	string = (char *)malloc(sizeof(char) * (nmemb * size));
	if (!string)
		return (NULL);
	ft_bzero(string, (nmemb * size));
	return (string);
}
