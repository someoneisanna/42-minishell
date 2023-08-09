/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:51:50 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:51:52 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <ctype.h>

int ft_isprint(int arg);

int main(void)
{
    char c = '4';
    printf("%i\n", ft_isprint(c));
    printf("%d\n", isprint(c));
}
*/

int	ft_isprint(int arg)
{
	if ((arg < 32 || arg > 126))
	{
		return (0);
	}
	return (1);
}
