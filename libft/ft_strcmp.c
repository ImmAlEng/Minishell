/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:09:29 by secker            #+#    #+#             */
/*   Updated: 2023/04/26 16:56:45 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	compare;

	if (s1 == NULL || s2 == NULL)
		return (0);
	compare = 0;
	while ((s1[compare] == s2[compare]) && (s1[compare] != '\0'
			&& s2[compare] != '\0'))
	{
		compare++;
	}
	return (s1[compare] - s2[compare]);
}
