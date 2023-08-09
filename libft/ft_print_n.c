/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:20 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:10:48 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_n(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += ft_print_c('-');
		n = -n;
	}
	if (n >= 10)
	{
		len += ft_print_n((n / 10));
		len += ft_print_n((n % 10));
	}
	else
		len += ft_print_c(n + '0');
	return (len);
}
