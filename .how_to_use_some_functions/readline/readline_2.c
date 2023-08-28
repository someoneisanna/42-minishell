/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:19:22 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 11:29:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	this is a simple example of how to use readline associated with some history functions

	REMEMBER TO COMPILE WITH -lreadline FLAG

	in this code, you can use the up and down arrows to navigate through the history of commands you used, just like in the terminal
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
		}
	}
}
