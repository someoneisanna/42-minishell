/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:01:30 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:50 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the two strings s1 and s2 until n characters or until a '\0'
 * is reached. Returns 0 if the strings are identical, otherwise returns the
 * difference between the first two differing bytes.
 * @param s1 String to be compared.
 * @param s2 String to be compared.
 * @param n Number of characters to be compared.
 * @return [0] if the strings are identical, otherwise returns the difference
 * between the first two differing bytes.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
