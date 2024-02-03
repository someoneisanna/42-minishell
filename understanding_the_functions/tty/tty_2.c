/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:21:04 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 16:25:40 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

/*
	we are still implementing ioctl, but now setting terminal attributes.

	in this program, you will be able to type something in the terminal, but what you type will not be displayed.
*/

int main(void)
{
	struct termios new_settings;
	if (ioctl(STDIN_FILENO, TCGETS, &new_settings) == -1)
	{
		printf("could not get the terminal attributes.\n");
		return (EXIT_FAILURE);
	}
	new_settings.c_lflag &= ~ECHO; // disable echo
	if (ioctl(STDIN_FILENO, TCSETS, &new_settings) == -1)
	{
		printf("could not set the terminal attributes.\n");
		return (EXIT_FAILURE);
	}
	printf("Type something: ");
	char buffer[100];
	scanf("%s", buffer);
	printf("\nYou typed: %s\n", buffer);
}
