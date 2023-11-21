/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels < iengels@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:05:14 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 23:05:57 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokens(char *s, t_dlist **t, int m_q[3])
{
	int				q;
	unsigned int	i;
	unsigned int	start;
	char			*tmp;

	start = 0;
	i = 0;
	q = 0;
	while (s[i])
	{
		m_q[2] = 0;
		while (ft_space_check(s[i], 0) == 0)
			i++;
		start = i;
		if (ft_is_operator(&s[i], q) != 0)
			i += ft_is_operator(&s[i], q);
		else
			ft_token_loop(s, &q, &i, &m_q);
		tmp = ft_substr(s, start, i - start);
		ft_add_dlist_back(&(*t), tmp, m_q[2]);
		free(tmp);
		tmp = NULL;
	}
}

unsigned int	ft_is_operator(char *s, unsigned int q)
{
	if (q != 0)
		return (0);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "|", 1) == 0)
		return (1);
	else
		return (0);
}

unsigned int	ft_num_of_flargs(t_dlist *v)
{
	unsigned int	count;

	count = 0;
	while (v != NULL)
	{
		count++;
		v = v->next;
	}
	return (1 + count);
}

void	ft_real_token_loop(t_dlist **v, t_tlist **t, unsigned int *i,
		t_tlist *p)
{
	if ((*v)->str[0] == '\0')
		;
	else if (ft_is_operator((*v)->str, 0) != 0 && (*v)->q == 0)
	{
		(*t)->op = ft_strdup((*v)->str);
		if ((*t)->flargs != NULL)
			(*t)->flargs[*i] = NULL;
		*i = 0;
		if ((*v)->next != NULL)
			ft_add_tlist_back(&p);
		*t = (*t)->next;
	}
	else if (t != NULL && (*t)->command == NULL)
		(*t)->command = ft_strdup((*v)->str);
	else if (t != NULL)
	{
		if ((*t)->flargs == NULL)
			(*t)->flargs = malloc(sizeof(char *) * (ft_num_of_flargs((*v)->next)
						+ 1));
		(*t)->flargs[*i] = ft_strdup((*v)->str);
		(*i)++;
	}
	*v = (*v)->next;
}

t_tlist	*ft_real_token(t_dlist *v, t_tlist *t, t_var *j)
{
	t_tlist			*p;
	unsigned int	i;

	if (j->id == 1)
		t = ft_create_tlist();
	p = t;
	if (j->id == 2)
	{
		ft_add_tlist_back(&p);
		while (t->next != NULL)
			t = t->next;
	}
	i = 0;
	while (v != NULL)
		ft_real_token_loop(&v, &t, &i, p);
	if (t != NULL && t->flargs != NULL)
		t->flargs[i] = NULL;
	return (p);
}
