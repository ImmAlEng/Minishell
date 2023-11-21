/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:36:56 by iengels           #+#    #+#             */
/*   Updated: 2022/10/24 17:00:16 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cont;

	if (!f || !del)
		return (0);
	new = 0;
	while (lst)
	{
		cont = ft_lstnew(f((*lst).content));
		if (!cont)
		{
			ft_lstclear(&cont, del);
			return (NULL);
		}
		ft_lstadd_back(&new, cont);
		lst = (*lst).next;
	}
	return (new);
}
