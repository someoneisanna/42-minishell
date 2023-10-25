/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:35:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Takes as a parameter an element and frees the memory of the element’s
 * content using the function ’del’ given as a parameter and free the element.
 * @param lst The element to free.
 * @param del The address of the function used to delete the content.
 * @return Nothing.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
	{
		return ;
	}
	del(lst->content);
	free(lst);
	lst = NULL;
}
