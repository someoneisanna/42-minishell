/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:15:15 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 12:27:24 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
	here we will join the fork and execve functions, which is necessary in the minishell and whenever you want to execute commands from you c program
*/

int main(void)
{
	char *path = "/bin/ls";
	char *args[] = {"ls", "-l", NULL};
	char *envp[] = {NULL};

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Child process will execute the command\n");
		if (execve(path, args, envp) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		printf("This line will not be printed\n");
	}
	else
	{
		wait(NULL);
		printf("Child process is done\n");
	}
}

/*
	notes:
	1) the child process will be executed first
	2) we need to use the fork with execve to make sure we don't exit the program after execve is executed or fails
	3) after the child process is done, the parent process will be executed
	4) in the project, we will use argv as our args and need to create a path function, because there are inumerous commands in the system with different paths and we need to find the right one. im not sure how we will use envp yet, but we will see
*/
