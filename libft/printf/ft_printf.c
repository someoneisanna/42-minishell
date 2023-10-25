/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:38 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 17:34:26 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *data, ...);
static char	ft_is_type(char c);
static int	ft_call_print(va_list ptr, char data_type);

int	ft_printf(const char *data, ...)
{
	int		i;
	int		bytes_printed;
	va_list	ptr;

	i = 0;
	bytes_printed = 0;
	va_start(ptr, data);
	while (data[i])
	{
		if (data[i] == '%' && ft_is_type(data[i + 1]))
		{
			bytes_printed += ft_call_print(ptr, data[i + 1]);
			i++;
		}
		else
			bytes_printed += ft_print_c(data[i]);
		i++;
	}
	va_end(ptr);
	return (bytes_printed);
}

static char	ft_is_type(char c)
{
	int		i;
	char	*type;

	i = 0;
	type = "cspdiuxX%";
	while (type[i])
	{
		if (type[i] == c)
			return (type[i]);
		i++;
	}
	return (0);
}

static int	ft_call_print(va_list ptr, char data_type)
{
	int	len;

	len = 0;
	if (data_type == '%')
		len = ft_print_c('%');
	else if (data_type == 'c')
		len = ft_print_c(va_arg(ptr, int));
	else if (data_type == 's')
		len = ft_print_s(va_arg(ptr, char *));
	else if (data_type == 'p')
		len = ft_print_p(va_arg(ptr, unsigned long));
	else if (data_type == 'd' || data_type == 'i')
		len = ft_print_n(va_arg(ptr, int));
	else if (data_type == 'u')
		len = ft_print_u(va_arg(ptr, unsigned int));
	else if (data_type == 'x')
		len = ft_print_x(va_arg(ptr, unsigned int), 'x');
	else if (data_type == 'X')
		len = ft_print_x(va_arg(ptr, unsigned int), 'X');
	return (len);
}
