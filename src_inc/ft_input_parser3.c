/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:13 by iengels           #+#    #+#             */
/*   Updated: 2023/04/25 15:11:44 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_my_flargdoc_helper(t_tlist *l, unsigned int *i, unsigned int *j,
		unsigned int *proof)
{
	if (l->command == NULL && l->next->flargs != NULL)
	{
		l->command = ft_strdup(l->next->flargs[(*j)++]);
		*proof = 1;
	}
	if (l->flargs != NULL)
	{
		while (l->flargs[*i] != NULL)
			(*i)++;
	}
	while (l->next->flargs[*j] != NULL)
		(*j)++;
	*j -= *proof;
}

char	**ft_add_flargs(t_tlist *l, t_var *v)
{
	unsigned int	i;
	unsigned int	j;
	char			**temp;
	unsigned int	proof;

	proof = 0;
	i = 0;
	j = 0;
	ft_my_flargdoc_helper(l, &i, &j, &proof);
	temp = (char **)malloc(sizeof(char *) * (i + j + 1));
	if (!temp)
		ft_free_and_exit(v, 1);
	temp[i + j] = NULL;
	while (j--)
		temp[i + j] = ft_strdup(l->next->flargs[j + proof]);
	if (l->flargs != NULL)
	{
		while (i--)
			temp[i] = ft_strdup(l->flargs[i]);
		free_stuff(l->flargs);
	}
	return (temp);
}

void	ft_handle_leftover(t_tlist *l, t_var *v)
{
	if (l->next->flargs != NULL)
		l->flargs = ft_add_flargs(l, v);
	if (l->next->op != NULL)
		l->op = ft_strdup(l->next->op);
	ft_del_node(l->next);
}

int	ft_get_heredoc(t_tlist *l, t_var *v)
{
	free(l->op);
	l->op = NULL;
	if (l->next == NULL)
	{
		ft_putstr_fd("minishell: syntax error near '\\n'\n", 2);
		return (1);
	}
	else
		l->doc = ft_add2(l, v);
	if (l->doc == NULL)
		return (1);
	ft_handle_leftover(l, v);
	return (0);
}

int	ft_post_processor(t_tlist **p, t_var *v)
{
	t_tlist	*l;

	l = *p;
	while (l != NULL)
	{
		if (l->op == NULL)
			l = l->next;
		else if (l->op[0] == '<' && l->op[1] == '<')
		{
			if (ft_get_heredoc(l, v) == 1)
				return (1);
		}
		else
			l = l->next;
	}
	return (0);
}
