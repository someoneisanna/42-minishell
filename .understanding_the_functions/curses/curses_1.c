/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:21:04 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 18:39:01 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>

/*
	here we will see how to use the tgetstr and tputs function.

	complilation: ccf curses_1.c -lcurses -ltermcap
*/

int main()
{
	char *term = getenv("TERM");

	if (tgetent(NULL, term) != 1)
	{
		perror("tgetent");
		return 1;
	}

	char *clear = tgetstr("cl", NULL);
	if (clear != NULL)
	{
		tputs(clear, 1, putchar);
	}
	else
	{
		fprintf(stderr, "Clear screen capability not found\n");
		return 1;
	}
	printf("Screen cleared using terminal capability.\n");
}
