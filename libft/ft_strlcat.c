/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:00:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:33 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the NULL-terminated string src to the end of dst. It will
 * append at most size - strlen(dst) - 1 bytes, NULL-terminating the result.
 * @param dest The string to append to.
 * @param src The string to be appended.
 * @param size The size of the destination buffer.
 * @return The total length of the string they tried to create.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	d;
	size_t	s;
	size_t	t;
	size_t	n;

	if ((dest == NULL) && (size == 0))
		return (0);
	s = ft_strlen(src);
	d = ft_strlen(dest);
	if (size < d)
		return (s + size);
	i = 0;
	n = size - d;
	t = d + s;
	while (((i + 1) < n) && src[i])
	{
		dest[d + i] = src[i];
		i++;
	}
	dest[d + i] = '\0';
	return (t);
}
