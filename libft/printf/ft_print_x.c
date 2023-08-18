/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:17:13 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x(unsigned long n, char base)
{
	int		len;
	char	*hex_base;

	len = 0;
	if (base == 'x')
		hex_base = "0123456789abcdef";
	else
		hex_base = "0123456789ABCDEF";
	if (n < 16)
		len += ft_print_c(hex_base[n]);
	else
	{
		len += ft_print_x(n / 16, base);
		len += ft_print_x(n % 16, base);
	}
	return (len);
}
