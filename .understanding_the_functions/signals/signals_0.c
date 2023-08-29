/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:13:19 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/18 18:40:04 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

/*
	SIGINT: ctrl + c -> 2
	SIGSTP: ctrl + z -> 20

	when you compile and run chdir_2.c and press ctrl + c, you will see that the prompt stops. this is because the shell is reacting  to the default signal handlers.

	here, we will make our program keep running even if we press ctrl + c by creating a custom signal handler.
	you can stop this program by pressing ctrl + z.

	there are two macros that can be used to set a signal handler:
	- SIG_IGN: ignore the signal. usage: signal(SIGINT, SIG_IGN);
	- SIG_DFL: set the default signal handler. usage: signal(SIGINT, SIG_DFL);
	it is not possible to ignore SIGKILL and SIGSTOP.
	we will see that in signals_1.c
*/

void sigint_handler(int sig)
{
	printf("  Signal received: %d\n", sig);
}

 int main(void)
 {
	 signal(SIGINT, sigint_handler);
	 while ((1));
 }
