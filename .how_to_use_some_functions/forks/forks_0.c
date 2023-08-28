/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:16:21 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 11:02:21 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
	this is a file that will help with the understanding of forks, without using the wait and waitpid functions

	reminder: we cannot use getpid in minishell
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
		printf("PARENT PROCESS #PID %d\n", getpid());
		printf("    #PID_VARIABLE = %d\n", pid);
	}
}

/*
	here, the result is that the parent process is executed first, and then the child process is executed
*/
