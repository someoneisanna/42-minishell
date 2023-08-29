/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 06:49:38 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/23 07:01:21 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/*
	here is an example of how to use the kill function
*/

void child_process()
{
	printf("Child process started. My PID: %d\n", getpid());
	while (1)
	{
		sleep(1);
	}
}

int main()
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (1);
    }
	else if (child_pid == 0)
	{
        child_process();
    }
	else
	{
		printf("Parent process started. Child PID: %d\n", child_pid);
		sleep(5);
		if (kill(child_pid, SIGTERM) == 0)
		{
			printf("Signal sent successfully to child process.\n");
		}
		else
		{
			perror("kill");
		}
		int status;
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child process exited with status: %d\n", WEXITSTATUS(status));
		}
	}
}

