/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:56:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/28 15:58:03 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
	this is a really small file explaining how to use unlink. it is in the pipes files because we could have used it in the pipex project (even though I didn't)

	what does it do? it deletes a file. it is the equivalent of rm in the shell.
*/

int main(void)
{
	const char *filename = "b.txt";

	if (unlink(filename) == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}

	printf("file %s deleted\n", filename);
}
