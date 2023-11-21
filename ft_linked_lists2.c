/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:19 by iengels           #+#    #+#             */
/*   Updated: 2023/04/27 12:35:04 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_dlist_back(t_dlist **lis, char *str, int q)
{
	t_dlist	*temp;

	if (!*lis)
	{
		*lis = ft_create_dlist(str, q);
		return ;
	}
	temp = *lis;
	while (temp->next)
		temp = temp->next;
	temp->next = ft_create_dlist(str, q);
	temp->next->prev = temp;
}

t_tlist	*ft_create_tlist(void)
{
	t_tlist	*new;

	new = malloc(sizeof(t_tlist));
	if (!new)
		return (NULL);
	new->op = NULL;
	new->doc = NULL;
	new->command = NULL;
	new->flargs = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->path = NULL;
	new->env = NULL;
	return (new);
}

void	ft_add_tlist_back(t_tlist **lis)
{
	t_tlist	*temp;

	if (!*lis)
	{
		*lis = ft_create_tlist();
		return ;
	}
	temp = *lis;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = ft_create_tlist();
	temp->next->prev = temp;
}
