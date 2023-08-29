/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:35:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 12:27:31 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	here, we will  understand how to use the other rl functions:
	- rl_on_new_line(): moves the cursor to the beginning of the next line
	- rl_replace_line(): replaces the contents of the readline buffer with text
	- rl_redisplay(): updates the display to reflect the new contents of the readline buffer

	i have no idea how and why we need this, and it is functioning weirdly. later one I will probably (hopefully) understand wtf is going on here
*/

int main(void)
{
	char *input;

	while ((input = readline("Enter a command: ")) != NULL)
	{
		if (input[0] != '\0')
		{
			add_history(input);
			printf("You entered: %s\n", input);
			free(input);
			rl_on_new_line();
			rl_replace_line("\n", 0);
			rl_redisplay();
			sleep(1);
		}
	}
}
