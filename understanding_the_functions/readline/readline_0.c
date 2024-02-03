/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:53 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 14:32:31 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	this is a very simple program that uses readline
	remember to compile with -lreadline
	steps to use readline:
		1. include the readline header
		2. use the readline function to get the input and save it into a string
		3. error handling for the readline function
		4. do what you want with the string you got from the prompt
		5. free the string
	BEWARE: READLINE CAN CAUSE MEMORY LEAKS ("STILL REACHABLE" IN VALGRIND)
		* the subject talks about it, saying that we shouldn't fix it
*/

int main(void)
{
	char *input = readline("Enter the text you want to be printed: ");
	if (input == NULL)
	{
		perror("readline");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", input);
	free(input);
}

/*
	some things readline can do:
	* read a line of text from an input stream (usually the terminal)
	* it allows the user to edit the line of text before submitting it
	* it provides history capabilities (it can store and recall previously entered lines of text)
	* it often includes tab-completion (it can complete partially typed commands or filenames)
*/
