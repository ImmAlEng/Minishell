/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fastgirl <fastgirl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:06:29 by iengels           #+#    #+#             */
/*   Updated: 2023/04/28 16:29:34 by fastgirl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_freelist(t_dlist *head)
{
	if (head->next != NULL)
		ft_freelist(head->next);
	free(head->str);
	head->str = NULL;
	free(head);
	head = NULL;
	return (NULL);
}

t_tlist	*ft_freetoken(t_tlist *l)
{
	int	i;

	if (l != NULL)
	{
		i = -1;
		ft_freetoken2(l);
		if (l->flargs != NULL)
		{
			while (l->flargs[++i] != NULL)
				free(l->flargs[i]);
			free(l->flargs);
		}
		free(l);
		l = NULL;
	}
	return (NULL);
}

void	ft_print_list(t_dlist *head)
{
	printf("Printlist:\n");
	while (head != NULL)
	{
		printf(":%s:\n", head->str);
		printf(":%i:\n", head->q);
		head = head->next;
	}
	printf("\n______________________________________\n");
}

void	ft_print_token(t_tlist *head)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	printf("Printtoken:\n");
	while (head != NULL)
	{
		printf("Token number:\t%i\n", i++);
		if (head->op != NULL)
			printf("op is:\t:%s:\n", head->op);
		if (head->command != NULL)
			printf("command is:\t:%s:\n", head->command);
		if (head->doc != NULL)
			printf("doc is:\t:%s:\n", head->doc);
		if (head->flargs != NULL)
		{
			while (head->flargs[j++] != NULL)
				printf("flarg[%i] is:\t:%s:\n", j, head->flargs[j]);
		}
		head = head->next;
	}
	printf("\n______________________________________\n");
}

t_dlist	*ft_create_dlist(char *str, int q)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->q = q;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
