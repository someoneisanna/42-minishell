/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:48:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 14:32:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
	this is a file that will help with the understanding of getcwd
	this is the function that will do what PWD does
*/

int main(void)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		printf("Current Directory: %s\n", cwd);
	else
	{
		perror("getcwd");
		return (1);
	}
	free(cwd);
}
