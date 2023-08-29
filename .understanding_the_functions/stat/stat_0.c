/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 07:03:45 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/23 07:12:10 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>

/*
	here is an example of how to use the stat function.

	used to get information about a file specified by its filename.

	int stat(const char *path, struct stat *buf);
	- path: path to the file
	- buf: pointer to a stat structure

*/

int main()
{
	const char *filename = "example.txt";
	struct stat file_info;

	if (stat(filename, &file_info) == 0)
	{
		printf("File size: %ld bytes\n", file_info.st_size);
		printf("File permissions: %o\n", file_info.st_mode & 0777);
	}
	else
	{
		perror("stat");
		return 1;
	}
}
