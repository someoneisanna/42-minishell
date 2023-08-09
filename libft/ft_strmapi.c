/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:01:12 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 19:01:13 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

char test_func(unsigned int i, char c) // increases every element by its index
{
	return (c + i);
}

int	main(void)
{
	char	str1[] = "abc";
	char	(*f)(unsigned int, char) = &test_func;

	printf("str1: %s\n", ft_strmapi(str1, (f)));
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	new = (char *)malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
