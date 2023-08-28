/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:36:44 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 12:11:02 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
	here we will understand a bit more of the execvp function
	prototype:
	int execve(const char *pathname, char *const argv[], char *const envp[]);
	parameters:
		pathname: path to the executable file
		argv: array of strings with the arguments to pass to the executable
		envp: array of strings with the environment variables to pass to the executable

*/

int main(void)
{
	char *args[] = {"ls", "-l", NULL}; // you need to put NULL at the end
	char *envp[] = {NULL};
	char *path = "/bin/ls";

	if (execve(path, args, envp) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	printf("This line will not be printed\n");
}
