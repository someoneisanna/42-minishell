/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:56:55 by ataboada          #+#    #+#             */
/*   Updated: 2023/06/20 14:50:05 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

char *ft_strchr(const char *str, int c);

int main(void)
{
    char s1[] = "teste";
	char a = '\0';

    printf("string: %s\nletter: %c\nresult: %s\n", s1, a, ft_strchr(s1, a));
}
*/

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (str[i])
	{
		if (str[i] == c1)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	if (str[i] == c1)
	{
		return ((char *)(str + i));
	}
	return (0);
}
