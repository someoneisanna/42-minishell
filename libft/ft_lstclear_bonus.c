/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:14 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:54:16 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

void ft_lstclear(t_list **lst, void (*del)(void *));

t_list *ft_lstnew(void *content)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *ptr;

	ptr = *lst;
	if (!ptr || !lst)
	{
		return ;
	}
	if (!(*lst))
	{
		*lst = ptr;
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = new;
}

int main(void)
{
	t_list **lst;
	char s1[] = "Hey";
	char s2[] = "There";
	char s3[] = "!";

	lst = (t_list **)calloc(1, sizeof(t_list *));
	*lst = ft_lstnew(s1);
	ft_lstadd_back(lst, ft_lstnew(s2));
	ft_lstadd_back(lst, ft_lstnew(s3));

	ft_lstclear(lst, free);

	printf("Node 0: %s\n", (char *)(*lst)->content);
	printf("Node 1: %s\n", (char *)(*lst)->next->content);
	printf("Node 2: %s\n", (char *)(*lst)->next->next->content);
}
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del || !*(lst))
	{
		return ;
	}
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	lst = 0;
}
