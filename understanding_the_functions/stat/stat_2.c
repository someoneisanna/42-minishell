/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:29:12 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 14:33:16 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*
	here is an example of how to use the fstat function.

	it is used to get information about a file specified by its file descriptor
*/

int main(void)
{
	const char *path = "example.txt";

	int fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	struct stat info;
	if (fstat(fd, &info) == -1)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}

	printf("File: %s\n", path);
	printf("File size: %lld bytes\n", (long long)info.st_size);
	printf("File mode: %o\n", info.st_mode & ~S_IFMT);

	close(fd);
}
