/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:03:10 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 19:03:12 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

int ft_tolower(int c);

int main(void)
{
    char a = 'A';
    char b = 'l';
    char c = '2';
    char d = 'Z';

    printf("%c\n", ft_tolower(a));
    printf("%c\n", ft_tolower(b));
    printf("%c\n", ft_tolower(c));
    printf("%c\n", ft_tolower(d));
}
*/

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	return (c);
}
