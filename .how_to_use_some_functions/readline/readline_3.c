/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:31:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 11:34:41 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	here we will show how rl_clear_history() works

	we use a function just like in readline_2, but you can see that we can't navigate through the history anymore
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
			rl_clear_history();
		}
	}
}
