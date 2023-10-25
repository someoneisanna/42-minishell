/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:57:10 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to the last occurrence of the character c in the
 * string s.
 * @param s The string to be scanned.
 * @param c The character to be searched.
 * @return A pointer to the last occurrence of the character c in the string s.
 */
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c1;

	i = ft_strlen(s);
	c1 = c;
	while (i >= 0)
	{
		if (s[i] == c1)
		{
			return ((char *)(s + i));
		}
		i--;
	}
	return (NULL);
}
