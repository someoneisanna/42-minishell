/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:50:45 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 14:54:17 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
	here we are using the getenv() function to get the value of some environment variables.
	we will probably use this in the export function of our shell.
*/

int		main(void)
{
	printf("HOME: %s\n", getenv("HOME"));
	printf("PATH: %s\n", getenv("PATH"));
	if (getenv("ROOT") == NULL)
		printf("ROOT: NOT defined\n");
	else
		printf("ROOT: %s\n", getenv("ROOT"));
	printf("USER: %s\n", getenv("USER"));
	return (0);
}
