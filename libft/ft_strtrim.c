/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:58:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/10 13:58:03 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ft_strtrim(char const *s1, char const *set);

int main(void)
{
    char s1[] = "   xxx   xxx";
	char s2[] = "testxxx ";
	char s3[] = "   x  x xxxxtexstxx  x ";
	char s4[] = "hello there :)";
	char s5[] = "   xxxx   ";
	char s6[] = "";
	char set1[] = " x";
	char set2[] = "123";
	char set3[] = "";
	printf("* The trimmed string is: %s\n", ft_strtrim(s1, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s2, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s3, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s4, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s5, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s6, set1));
	printf("The trimmed string is: %s\n", ft_strtrim(s1, set2));
	printf("* The trimmed string is: %s\n", ft_strtrim(s6, set2));
	printf("* The trimmed string is: %s\n", ft_strtrim(s6, set3));
}
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
