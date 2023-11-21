/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_truncate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:04:18 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 15:14:42 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_get_variable_size(char *s, unsigned int *j, t_var *v)
{
	char			*name;
	char			*value;
	unsigned int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	if (ft_get_qvar_size(s, &j, &i, v) != 0)
		return (1);
	while (s[i] && s[i] != 32 && s[i] != 39 && s[i] != 34)
		i++;
	name = malloc(i + 1);
	name[i] = '\0';
	while (i--)
		name[i] = s[i];
	value = ft_get_own_env(name, v);
	i = ft_strlen(name);
	free(name);
	if (value != NULL)
	{
		*j += ft_strlen(value);
		free(value);
	}
	return (i);
}

unsigned int	ft_new_size(char *s, int m_q[3], t_var *v)
{
	unsigned int	i;
	unsigned int	q;
	unsigned int	j;

	ft_set_to_zero(&i, &q, &j);
	while (s[i])
	{
		if ((q == 0 && (s[i] == '\'' || s[i] == '\"')) && ((m_q[0] != 0
					&& s[i] == '\"') || (m_q[1] != 0 && s[i] == '\'')))
		{
			m_q[s[i] % 2]--;
			q = 1 + (s[i] % 2);
		}
		else if ((q == 2 && s[i] == 39) || (s[i] == 34 && q == 1))
		{
			m_q[s[i] % 2]--;
			q = 0;
		}
		else if (q != 2 && s[i] == '$')
			i += ft_get_variable_size(&s[i + 1], &j, v);
		else
			j++;
		i++;
	}
	return (j);
}

unsigned int	ft_get_variable(char *s1, char *s2, unsigned int *d, t_var *v)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	if (s2[0] == '\0')
		return (0);
	if (ft_strncmp(s2, "?\"", 2) == 0 || ft_strncmp(s2, "?", 2) == 0
			|| ft_strncmp(s2, "? ", 2) == 0)
		return (ft_get_qvariable(s1, &d, v));
	while (s2[i] && s2[i] != 32 && s2[i] != 39 && s2[i] != 34)
		i++;
	name = ft_init_name(s2, &i, v);
	value = ft_get_own_env(name, v);
	if (value == NULL)
		return (ft_free_name_return_i(&name));
	while (value[++i] != '\0')
		s1[(*d)++] = value[i];
	i = ft_strlen(name);
	free(name);
	if (value != NULL)
		free(value);
	return (i);
}

char	*ft_truncate_helper(char *s, int m_q[3], t_var *v)
{
	int				i;
	unsigned int	q;
	char			*new;
	unsigned int	j;
	int				q_q[3];

	ft_copy_int_array(&q_q, m_q, 3);
	ft_initialize_truncate(&i, &q, &j);
	new = malloc(1 + ft_new_size(s, q_q, v));
	if (!new)
		ft_free_and_exit(v, 1);
	while (s[++i])
	{
		if (ft_askopen_qstatus(q, m_q, s[i]) == 1)
			ft_change_q_status(&q, m_q, s[i], 0);
		else if ((q == 2 && s[i] == 39) || (s[i] == 34 && q == 1))
			ft_change_q_status(&q, m_q, s[i], 1);
		else if (q != 2 && s[i] == '$')
			i += ft_get_variable(new, &s[i + 1], &j, v);
		else
			new[j++] = s[i];
	}
	new[j] = '\0';
	free(s);
	return (new);
}

void	ft_truncate(t_dlist **p, int q[3], t_var *v)
{
	t_dlist	*t;
	int		q_q[3];

	ft_copy_int_array(&q_q, q, 3);
	t = *p;
	while (t != NULL)
	{
		t->str = ft_truncate_helper(t->str, q_q, v);
		t = t->next;
	}
}
