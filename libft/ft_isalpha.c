/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:51:14 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:51:17 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <ctype.h>

int ft_isalpha(int arg);

int main(void)
{
    char c = 'j';
    printf("%i\n", ft_isalpha(c));
    printf("%d\n", isalpha(c));
}
*/

int	ft_isalpha(int arg)
{
	if ((arg < 65 || arg > 90) && (arg < 97 || arg > 122))
	{
		return (0);
	}
	return (1);
}
