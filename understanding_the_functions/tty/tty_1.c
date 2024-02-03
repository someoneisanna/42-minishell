/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:34 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 16:20:45 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

/*
	here we will implement ioctl, which is used to control the terminal.

	in this file, we will use ioctl to get the size of the terminal.
*/

int main(void)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) // TIOCGWINSZ is a macro that expands to an integer constant
	{
		printf("could not get the size of the terminal.\n");
		return (EXIT_FAILURE);
	}
	printf("Terminal width: %d\n", ws.ws_col);
	printf("Terminal height: %d\n", ws.ws_row);
}
