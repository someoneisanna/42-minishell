/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:33:19 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 16:43:08 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/*
	here we will learn how to use tcsetattr and tcgetattr.

	they are used to manipulate and retrieve terminal attributes.

	tcsetattr is used to set the terminal attributes, and tcgetattr is used to get them.

	int this program, we will disable echo.

	while these functions are used specially to manipulate terminal attributes, ioctl is a more general-purpose mechanism for performing device-specific operations.
*/

int main(void)
{
	struct termios orig_settings, new_settings;

	if (tcgetattr(STDIN_FILENO, &orig_settings) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	new_settings = orig_settings;
	new_settings.c_lflag &= ~ECHO; // disable echo

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_settings) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}

	printf("Enter password: ");
	char password[100];
	scanf("%s", password);
	printf("\nYou entered: %s\n", password);
}
