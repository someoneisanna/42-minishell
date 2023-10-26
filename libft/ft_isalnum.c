/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:50:56 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 17:21:35 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>
/**
 * @brief Checks if the passed character is a number or a letter.
 * @param c Character to be checked.
 * @return [1] if c is a number, [2] if c is a letter, [0] otherwise.
 */
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57))
	{
		return (1);
	}
	else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}
