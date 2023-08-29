/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:01:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 16:15:24 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
	here we will understand how to use the functions associated with the tty (teletype) files. these files are the files that are used to communicate with the terminal.
	they are located in /dev/tty* (tty0, tty1, tty2, etc).
	the tty0 file is the current terminal. the tty1 file is the first terminal, tty2 is the second, etc.
	the tty files are used to communicate with the terminal. for example, when you type something in the terminal, the tty file is used to read what you typed.
	when you want to print something in the terminal, the tty file is used to write what you want to print.
	the tty files are also used to get the size of the terminal, to get the cursor position, etc.

	here we will look at three different functions:
	isatty: used to check if a file descriptor is associated with a terminal.
	ttyname: used to get the name of the terminal associated with a fd.
	ttyslot: used to get the number of the current terminal.

	not sure yet about how we will need this, but we will see later.
*/

int main(void)
{
	int fd = 0; // the file descriptor of the current terminal.

	if (isatty(fd))
	{
		printf("fd %d is associated with a terminal.\n", fd);
		char *terminal_name = ttyname(fd);
		if (terminal_name)
			printf("the name of the terminal is %s.\n", terminal_name);
	}
	else
		printf("fd %d is not associated with a terminal.\n", fd);

	int terminal_number = ttyslot();
	if (terminal_number > 0)
		printf("the number of the current terminal is %d.\n", terminal_number);
	else
		printf("could not get the number of the current terminal.\n");
}
