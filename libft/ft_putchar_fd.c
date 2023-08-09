/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:57:35 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:57:36 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <unistd.h>

void ft_putchar_fd(char c, int fd);

int main(void)
{
    ft_putchar_fd('a', 1);
    ft_putchar_fd('\n', 1);
}
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
