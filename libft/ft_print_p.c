/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:26 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:45:04 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(unsigned long n)
{
	int	len;

	len = 0;
	if (!n)
	{
		ft_print_s("(nil)");
		return (5);
	}
	len += ft_print_s("0x");
	len += ft_print_x(n, 'x');
	return (len);
}
