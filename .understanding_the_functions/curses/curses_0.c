/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:51:13 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 18:22:54 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

/*
	the functions tgetent, tgetflag, tgetnum, tgetstr, and tgoto will be implemented in this and the next file.

	compilation: ccf curses_0.c -lcurses

	tgetent: used to retrieve the termcap database entry for the terminal type specified by the argument name.
	tgetflag: used to retrieve the boolean value of the termcap capability specified by the argument id.
	tgetnum: used to retrieve the numeric value of the termcap capability specified by the argument id.
	tgetstr: used to retrieve the string value of the termcap capability specified by the argument id.
	tgoto: used to retrieve the string value of the termcap capability specified by the argument id.
*/

int main(void)
{
	char *termtype = getenv("TERM");

	if (tgetent(NULL, termtype) != 1)
	{
		perror("tgetent");
		exit(EXIT_FAILURE);
	}

	if (tgetflag("am") == 1)
		printf("automatic margins: true\n");
	else
		printf("automatic margins: false\n");

	int cols = tgetnum("co");
	if (cols != -1)
		printf("number of columns: %d\n", cols);
	else
	{
		perror("tgetnum");
		exit(EXIT_FAILURE);
	}
}
