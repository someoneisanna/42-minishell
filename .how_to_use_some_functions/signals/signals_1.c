/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:37 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 18:39:44 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/*
	here we will deal with signals and forks to understand when parents and children are handling signals in the same way.

	if you use signal(SIGINT, SIG_IGN) in a parent process, the child processes will inherit the signal handler.
	if you dont want that, use signal(SIGINT, SIG_DFL) in the child process.

	in this first main, we will ignore the SIGINT signal, so the child will ignore it too. that means that the child will not exit the loop when you press ctrl + c.

	int the second main, it will be the opposite, the child will not ignore the signal, so it will exit the loop when you press ctrl + c.
*/


/* int main()
{
	int pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		while (1);
	}
	else
		wait(NULL);
} */

int main()
{
	int pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // the difference is here
		while (1);
	}
	else
		wait(NULL);
}
