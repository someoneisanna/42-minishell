/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:50:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:50:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <strings.h>

void ft_bzero(void *s, size_t n);

int main(void)
{
    char str[] = "Anna Carolina";
    char *str1 = str;

    bzero(str + 5, 5 * sizeof(char));
    printf("After real function: %s\n", str);

    ft_bzero(str1 + 5, 5 * sizeof(char));
    printf("After my function:   %s\n", str1);
}
*/

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		*(str + i) = '\0';
		i++;
	}
}
