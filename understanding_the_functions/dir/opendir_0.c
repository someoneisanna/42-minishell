/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:35:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 14:40:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/*
	here we will interact with some functions that involve directories.

	opendir: opens a directory stream
		DIR *opendir(const char *dirname);
	readdir: reads a directory stream
		struct dirent *readdir(DIR *dirp);
	closedir: closes a directory stream
		int closedir(DIR *dirp);

	they are used to list the files in a directory
*/

int main(void)
{
	const char *path = "..";

	DIR *dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
 }
