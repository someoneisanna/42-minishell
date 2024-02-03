/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:41:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 19:26:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
	here we will understand how to use sigaction() and sigemptyset() functions.

	signal() is generally not recommended, since it has some portability issues. it is recommended to use sigaction instead.

	prototype:
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

	its struct contains:
	struct sigaction {
		void     (*sa_handler)(int);
		void     (*sa_sigaction)(int, siginfo_t *, void *);
		sigset_t   sa_mask;
		int        sa_flags;
		void     (*sa_restorer)(void);
	};
*/

void signal_handler(int signum)
{
	printf("  Received SIGINT signal (%d)\n", signum);
}

int main()
{
	struct sigaction s;

	sigemptyset(&s.sa_mask); // this initializes the structure
	s.sa_handler = signal_handler;
	s.sa_flags = 0;

	if (sigaction(SIGINT, &s, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	printf("Press Control + C to trigger SIGINT...\n");
	while (1)
	{
		// This will keep the program running until Control + Z
	}
}
