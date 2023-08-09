/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:56:20 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:56:22 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>

void *ft_memchr(const void *str, int c, size_t n);

int main(void)
{
    char str[] = "Hello There";
    char c = 'o';
    char *s;
    char *t;

    s = ft_memchr(str, c, 4);
    t = ft_memchr(str, c, 5);

    printf("String after '%c' is '%s'\n", c, s);
    printf("String after '%c' is '%s'\n", c, t);

}
*/

void	*ft_memchr(const void *str, int c, size_t n)
{
	char		*s;
	size_t		i;

	s = (char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (char)c)
		{
			return (&s[i]);
		}
		i++;
	}
	return (NULL);
}
