/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:59:46 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/08 18:59:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ft_striteri(char *s, void (*f)(unsigned int, char *));

void test_func(unsigned int i, char *s) // increases every element by its index
{
	*s += i;
}

int	main(void)
{
	char	str1[] = "abc";
	void	(*f)(unsigned int, char *) = &test_func;

	ft_striteri(str1, (f));
	printf("str1: %s\n", str1);
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!s)
	{
		return ;
	}
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
