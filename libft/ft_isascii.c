/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:51:25 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:51:27 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <ctype.h>

int ft_isascii(int arg);

int main(void)
{
    char c = '.';
    printf("%i\n", ft_isascii(c));
    printf("%d\n", isascii(c));
}
*/

int	ft_isascii(int arg)
{
	if ((arg < 0 || arg > 127))
	{
		return (0);
	}
	return (1);
}
