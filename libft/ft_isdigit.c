/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:51:39 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:51:41 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <ctype.h>

int ft_isdigit(int arg);

int main(void)
{
    char c = '9';
    printf("%i\n", ft_isdigit(c));
    printf("%d\n", isdigit(c));
}
*/

int	ft_isdigit(int arg)
{
	if ((arg < 48 || arg > 57))
	{
		return (0);
	}
	return (1);
}
