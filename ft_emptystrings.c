/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emptystrings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:10 by iengels           #+#    #+#             */
/*   Updated: 2023/04/27 00:20:14 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_printable(char c)
{
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

int	ft_check_inputline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_printable(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_init_name(char *s2, int *i, t_var *v)
{
	char	*name;

	name = malloc((*i) + 1);
	if (!name)
		ft_free_and_exit(v, 1);
	name[*i] = '\0';
	while ((*i)-- > 0)
		name[*i] = s2[*i];
	return (name);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*new;

	tmp1 = ft_strjoin(s1, s2);
	new = ft_strjoin(tmp1, s3);
	free(tmp1);
	return (new);
}
