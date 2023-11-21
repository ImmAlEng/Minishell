/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:17:19 by iengels           #+#    #+#             */
/*   Updated: 2022/10/24 14:50:20 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_null(long int num)
{
	char	*new;

	if (num < 1)
	{
		new = ft_calloc(1, 2);
		if (!new)
			return (NULL);
		new[0] = '0';
		return (new);
	}
	return (NULL);
}

static unsigned int	ft_digitcount(long int num)
{
	unsigned int	count;

	count = 0;
	if (num < 0)
	{
		count++;
		num *= -1;
	}
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int		num;
	char			*new;
	long int		single;
	unsigned int	i;

	num = n;
	i = ft_digitcount(num);
	if (num == 0)
		return (ft_null(num));
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i--] = '\0';
	if (num < 0)
	{
		num *= -1;
		new[0] = '-';
	}
	while (num != 0)
	{
		single = num;
		new[i--] = single % 10 + 48;
		num /= 10;
	}
	return (new);
}
