/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:50:56 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:50:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <ctype.h>

int ft_isalnum(int arg);

int main(void)
{
    char c = '=';
    printf("%i\n", ft_isalnum(c));
    printf("%d\n", isalnum(c));
}
*/

int	ft_isalnum(int arg)
{
	if ((arg >= 48 && arg <= 57))
	{
		return (1);
	}
	if ((arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122))
	{
		return (2);
	}
	return (0);
}
