/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:29 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:50:27 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		ft_print_s("(null)");
		return (6);
	}
	while (s[len])
	{
		ft_print_c(s[len]);
		len++;
	}
	return (len);
}
