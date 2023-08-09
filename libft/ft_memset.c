/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:57:20 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:57:21 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <string.h>

void *ft_memset(void *ptr, int x, size_t n);

int main(void)
{
    char str[] = "Anna Carolina";
    char *str1 = str;

    memset(str + 5, '2', 5 * sizeof(char));
    printf("After real function: %s\n", str);

    ft_memset(str1 + 5, '2', 5 * sizeof(char));
    printf("After my function:   %s\n", str1);
}
*/

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = ptr;
	while (i < n)
	{
		*(str + i) = x;
		i++;
	}
	return (str);
}
