/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:58:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:38:02 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a copy of ’s1’ with the
 * characters specified in ’set’ removed from the beginning and the end of the
 * string.
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	b;
	size_t	e;

	if (!s1 || !set)
		return (NULL);
	b = 0;
	while (ft_strchr(set, s1[b]) && s1[b])
		b++;
	e = ft_strlen(s1);
	while (ft_strchr(set, s1[e - 1]) && e > b)
		e--;
	new = (char *)malloc((sizeof(char)) * (e - b + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (b < e)
	{
		new[i] = s1[b];
		i++;
		b++;
	}
	new[i] = '\0';
	return (new);
}
