/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:38 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/19 13:10:21 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//#include <stdio.h>
//#include <limits.h>

int			ft_printf(const char *data, ...);
static char	ft_is_type(char c);
static int	ft_call_print(va_list ptr, char data_type);

/*
int main(void)
{
	int i1 = INT_MIN;
	int i2 = INT_MAX;
	long l1 = LONG_MAX;
	long l2 = LONG_MIN;
	unsigned int u1= UINT_MAX;
	unsigned int u2= 444;
	char c1 = '1';
	char c2 = 'a';
	char *s1 = "anna";
	char *s2 = "how are you?";
	unsigned int *ptr1 = &u1;
	unsigned int *ptr2 = &u2;
	printf("%c, %c\n", c1, c2);
	ft_printf("%c, %c\n", c1, c2);
	printf("%s, %s\n", s1, s2);
	ft_printf("%s, %s\n", s1, s2);
	printf("%p, %p\n", ptr1, ptr2);
	ft_printf("%p, %p\n", ptr1, ptr2);
	printf("%d, %d\n", i1, i2);
	ft_printf("%d, %d\n", i1, i2);
	printf("%i, %i\n", i1, i2);
	ft_printf("%i, %i\n", i1, i2);
	printf("%u, %u\n", u1, u2);
	ft_printf("%u, %u\n", u1, u2);
	printf("%x, %x\n", u1, u2);
	ft_printf("%x, %x\n", u1, u2);
	printf("%X, %X\n", u1, u2);
	ft_printf("%X, %X\n", u1, u2);
}
*/

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
