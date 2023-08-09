/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:00:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 19:00:18 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>

size_t ft_strlcat (char *dest, const char *src, size_t size);

int main(void)
{
    char *s = "there";
    char d[100] = "hey ";

    printf("%li\n", ft_strlcat(d, s, 13));
    printf("%s\n", d);
}
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
