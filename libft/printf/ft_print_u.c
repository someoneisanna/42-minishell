/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:31 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:10:37 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*min int: 0, maximum int: 4,294,967,295*/

int	ft_print_u(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_print_u((n / 10));
		len += ft_print_u((n % 10));
	}
	else
		len += ft_print_c(n + '0');
	return (len);
}
