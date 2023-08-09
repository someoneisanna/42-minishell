/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:55:18 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:55:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

t_list *ft_lstlast(t_list *lst);

int main(void)
{
	void *content = (char *)content;

	t_list *head = NULL;
	head = (t_list *) malloc(sizeof(t_list));

	head->content = "1";
	head->next = (t_list *) malloc(sizeof(t_list));
	head->next->content = "2";
	head->next->next = NULL;

	t_list *ptr;
	ptr = ft_lstlast(head);

	printf("%s\n", (char *)ptr->content);
}
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	if (!ptr)
	{
		return (ptr);
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}
