/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:51:39 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:35:10 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the passed character is a digit.
 * @param c Character to be checked.
 * @return [1] if c is a digit, [0] otherwise.
 */
int	ft_isdigit(int c)
{
	if ((c < 48 || c > 57))
	{
		return (0);
	}
	return (1);
}
