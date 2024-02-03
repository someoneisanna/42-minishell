/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:30:19 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 11:37:07 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
	this is a file that will help with the understanding of forks, this time using the wait/waitpid functions
*/

int main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("CHILD PROCESS  #PID %d\n", getpid());
		printf("    #PID_VARIABLE = %d\n", pid);
	}
	else
	{
		wait(NULL);
		printf("PARENT PROCESS #PID %d\n", getpid());
		printf("    #PID_VARIABLE = %d\n", pid);
	}
}

/*
	here, the result is that the child process is executed first, and then the parent process is executed
*/
