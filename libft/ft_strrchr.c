/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:57:10 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/10 14:00:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>

char *ft_strrchr(const char *str, int c);

int main(void)
{
    char s1[] = "tripouille";
    printf("letter: %c\nadress: %p\nanswer: %p, %s\n", s1[0], &s1[0], 
    	ft_strrchr(s1, 't' + 256), ft_strrchr(s1, 't' + 256));
}
*/

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	c1;

	i = ft_strlen(str);
	c1 = c;
	while (i >= 0)
	{
		if (str[i] == c1)
		{
			return ((char *)(str + i));
		}
		i--;
	}
	return (NULL);
}
