/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:33:08 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 14:51:40 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
	this is a file that will help with the understanding of chdir
	here, we have an issue. chdir is the function we need to use to implement cd
	however, chdir forks a new process, and therefore, the directory changes in the child process only. although successful, the parent process remains in the same directory. in chdir_2.c we will see how to solve this issue.
*/

int change_directory(const char *new_dir)
{
	if (chdir(new_dir) != 0)
	{
		perror("chdir");
		return (1);
	}
	return (0);
}

int main(void)
{
	const char *new_dir = "/home/anna/Desktop/42-minishell";

	if (change_directory(new_dir) == 0)
		printf("Directory changed to %s\n", new_dir);
	else
	{
		perror("change_directory");
		return (1);
	}
}


