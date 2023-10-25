/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:57:20 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:36:37 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the
 * constant byte c.
 * @param s String to be filled.
 * @param x Constant byte to fill with.
 * @param n Number of bytes to be filled.
 * @return String s.
 */
void	*ft_memset(void *s, int x, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		*(str + i) = x;
		i++;
	}
	return (str);
}
