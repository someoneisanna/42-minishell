/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 07:09:04 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 14:28:24 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
	here is an example of how to use the lstat function.

	how to create a symbolic link? ln -s <target> <link_name>

	function: is used to get information about a symbolic link specified by its filename

	int lstat(const char *path, struct stat *buf);
	- path: path to the symbolic link
	- buf: pointer to a stat structure
*/

int main(void)
{
	const char *path = "symbolic_link";
	struct stat info;

	if (lstat(path, &info) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	printf("File: %s\n", path);
	printf("File size: %lld bytes\n", (long long)info.st_size);
    printf("File mode: %o\n", info.st_mode & ~S_IFMT);
}

/*
	the size is the size of the symbolic link file, not the size of the target file.
	the target file has a size of 26 bytes (as you can see with stat)
	the symbolic link file has a size of 75, which is the size of the path to the target file (the length of the path, in this case: /home/anna/Desktop/42-minishell/.how_to_use_some_functions/stat/example.txt)
*/
