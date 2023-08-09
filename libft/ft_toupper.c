/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:03:18 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 19:03:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

int ft_toupper(int c);

int main(void)
{
    char a = 'a';
    char b = 'L';
    char c = '2';
    char d = 'z';

    printf("%c\n", ft_toupper(a));
    printf("%c\n", ft_toupper(b));
    printf("%c\n", ft_toupper(c));
    printf("%c\n", ft_toupper(d));
}
*/

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	return (c);
}
