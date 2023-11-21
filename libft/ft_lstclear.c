/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:19:35 by iengels           #+#    #+#             */
/*   Updated: 2022/10/24 16:29:27 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*swap;

	if (!(*lst) || !del)
		return ;
	new = *lst;
	while (new != NULL)
	{
		del(new->content);
		swap = new;
		new = new->next;
		free(swap);
	}
	*lst = NULL;
}
