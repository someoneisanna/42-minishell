/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:56:55 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:16 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of ’c’ in the string pointed to by ’str’.
 * @param s String to be scanned.
 * @param c Character to be searched.
 * @return Pointer to the located character, or NULL if the character does not
 * appear in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (s[i])
	{
		if (s[i] == c1)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == c1)
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
