/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:55:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 15:14:55 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
	the concept and implementation of pipes were learned and done in the pipex project. i will copy what I have done there, so that it can be understood more clearly. this first file is a very simple introduction. the others are more complicated.
*/

int main(void)
{
	// creation of the pipe
	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// child process
	else if (pid == 0)
	{
		close(pipefd[1]); // close the write end of the pipe
		char msg[100];
		read(pipefd[0], msg, 100); // read from the read end of the pipe
		printf("Message received: %s\n", msg);
		close(pipefd[0]); // close the read end of the pipe
	}
	// parent process
	else
	{
		close(pipefd[0]); // close the read end of the pipe
		char message[] = "Hello, world!";
		write(pipefd[1], message, sizeof(message)); // write to the write end of the pipe
		close(pipefd[1]); // close the write end of the pipe
		wait(NULL);
	}

}
