/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curses_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:37:23 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 18:43:48 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>

/*
	here we will see how to use the tgoto function.

	compilation: ccf curses_2.c -lcurses -ltermcap

	very confusing. i have no idea how to work with this.
*/

int main()
{
	char *term = getenv("TERM");

	if (tgetent(NULL, term) != 1)
	{
		perror("tgetent");
		return 1;
	}

	char *goto_position = tgoto(tgetstr("cm", NULL), 10, 5);

	if (goto_position != NULL)
	{
		tputs(goto_position, 1, putchar);
		printf("Cursor is now positioned at row 5, column 10\n");
	}
	else
	{
		perror("tgoto");
		return 1;
	}
}

