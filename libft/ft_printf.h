/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:54:42 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/14 15:16:31 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
//# include <limits.h>

int	ft_printf(const char *data, ...);
int	ft_print_c(char c);
int	ft_print_s(char *s);
int	ft_print_p(unsigned long n);
int	ft_print_n(long n);
int	ft_print_u(unsigned int n);
int	ft_print_x(unsigned long n, char base);

#endif
