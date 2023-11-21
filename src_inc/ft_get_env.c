/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:17:43 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 22:12:32 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_name_return_i(char **name)
{
	unsigned int	i;

	i = ft_strlen(*name);
	free(*name);
	return (i);
}

int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s1[i] != c)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s2[i] != '\0' && s1[i] == c)
		return (-1);
	return (0);
}

char	*ft_get_envvarpos(char *s)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (s[i] == '\0')
		return (NULL);
	while (s[i] && s[i] != '=')
		i++;
	return (&s[i + 1]);
}

char	*ft_get_own_env(char *s, t_var *v)
{
	t_dlist	*l;
	char	*env;

	l = v->exp;
	while (l != NULL)
	{
		if (ft_is_variable(l->str) == 0 && (ft_strccmp(l->str, s, '=') == 0))
		{
			env = ft_strdup(ft_get_envvarpos(l->str));
			return (env);
		}
		l = l->next;
	}
	return (NULL);
}
