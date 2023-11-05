/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:50:56 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/04 21:31:29 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		return (2);
	}
	return (0);
}
