/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:21 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:09:54 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_dlist_pointers(t_tlist *l)
{
	if (l->next == NULL)
		l->prev->next = NULL;
	else
	{
		if (l->prev != NULL)
			l->prev->next = l->next;
		if (l->next != NULL)
			l->next->prev = l->prev;
	}
	if (l->prev == NULL)
		l->next->prev = NULL;
	else
	{
		if (l->next != NULL)
			l->next->prev = l->prev;
		if (l->prev != NULL)
			l->prev->next = l->next;
	}
}

void	ft_del_node(t_tlist *l)
{
	int	i;

	i = 0;
	if (l->op != NULL)
		free(l->op);
	if (l->command != NULL)
		free(l->command);
	if (l->flargs != NULL)
	{
		while (l->flargs[i] != NULL)
		{
			free(l->flargs[i]);
			i++;
		}
		free(l->flargs);
	}
	if (l->path != NULL)
		free(l->path);
	if (l->env != NULL)
		free(l->env);
	ft_set_dlist_pointers(l);
	free(l);
}

int	ft_lis_and_token(t_var *v, t_dlist **l, t_tlist **lis)
{
	int	q[3];
	int	c_q[3];

	ft_last_quote(v->input, &q);
	ft_copy_int_array(&c_q, q, 3);
	*l = NULL;
	ft_tokens(v->input, &(*l), q);
	ft_truncate(&(*l), c_q, v);
	*lis = ft_real_token(*l, *lis, v);
	ft_freelist(*l);
	v->head = *lis;
	if (ft_post_processor(lis, v) == 1)
		return (1);
	ft_get_command_path(*lis);
	ft_incomplete(*lis, v);
	v->count_token = ft_count_token(*lis);
	return (0);
}

int	ft_count_digits(int n)
{
	if (n < 0)
		return (1 + ft_count_digits(-n));
	if (n < 10)
		return (1);
	return (1 + ft_count_digits(n / 10));
}

unsigned int	ft_get_qvar_size(char *s, unsigned int **j, unsigned int *i,
		t_var *v)
{
	(void)v;
	if (s[*i] != '\0')
	{
		if (s[*i] == '?')
		{
			if (s[*i + 1] == '\0' || s[*i + 1] == 32 || s[*i + 1] == '\"')
			{
				**j += ft_count_digits(g_status);
				return (1);
			}
		}
	}
	return (0);
}
