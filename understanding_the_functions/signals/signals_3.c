/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:50:57 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/19 15:49:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

/*
	in this file, we will see how to use the following functions:
	- sigemptyset: initialize an empty signal set
	- sigaddset: add a signal to the signal set
	- sigismember -> we can't use this function in minishell

	what is a signal set?
	- is a data structure used in operating systems to represent a collection or set of signals.
	- in Unix-like systems, signals are asynchronous notifications sent to processes to notify them about various events, such as the termination of a child process, keyboard interrupts (Ctrl+C), and more.

*/

int main()
{
	sigset_t set;
	int signal_num = SIGINT;

	// Initialize an empty signal set
	if (sigemptyset(&set) != 0)
	{
		perror("sigemptyset");
		return (1);
	}

	// Add a signal to the signal set
	if (sigaddset(&set, signal_num) != 0)
	{
		perror("sigaddset");
		return 1;
	}

	// Check if a signal is in the signal set
	if (sigismember(&set, signal_num) == 1)
		printf("Signal %d is in the set.\n", signal_num);
	else
	{
		printf("Signal %d is not in the set.\n", signal_num);
	}
}

