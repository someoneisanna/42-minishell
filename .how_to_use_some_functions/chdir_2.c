/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:11:46 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 17:55:00 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>

#include "../libft/libft.h"

/*
	here we will see how to solve the issue of chdir_1.c

	we will use fork() and waitpid() to make sure the parent process changes directory as well

	we use strtok() to parse the input string into an array of strings (this is kinda like split, but everytime it is called, it returns a word from the string)
	we will also use execvp instead of execve to make it easier
	this function kind of creates a minishell already

	why it seems we are in an inifinite loop? because when shell executes the command, it creates a new child process. once the child process is done and returns a result, the parent process will wait for it to finish and then it will execute the next command. this is why we are in an infinite loop, because the parent process never finishes, it just waits for the child process to finish and then it executes the next command.

	compile: ccf chdir_2.c ../libft/libft.a -lreadline
*/

int cd(char *path)
{
	return chdir(path);
}

int main()
{
	char **command;
	char *input;
	pid_t child_pid;

	while (1)
	{
		input = readline("prompt> ");
		command = ft_split(input, ' ');
		if (!command[0])
		{
			free(input);
			free(command); // free_split
			continue;
		}
		if (strcmp(command[0], "cd") == 0)
		{
			if (cd(command[1]) < 0)
				perror(command[1]);
			continue;
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (child_pid == 0)
		{
			if (execvp(command[0], command) < 0)
			{
				perror(command[0]);
				exit(1);
			}
		}
		else
			wait(NULL);
		free(input);
		int i = 0;
		while (command[i]) // this is free_split
		{
			free(command[i]);
			i++;
		}
		free(command);
	}
}
