/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:34:25 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 13:45:36 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	here we will use the readline function, as well as fork and execve
	remember to compile with -lreadline
*/

int main(void)
{
	char *input = readline("Enter the text you want to be printed: ");
	if (input == NULL)
	{
		perror("readline");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *argv[] = {"echo", input, NULL};
		char *envp[] = {NULL};
		char *path = "/bin/echo";
		if (execve(path, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	free(input);
}
