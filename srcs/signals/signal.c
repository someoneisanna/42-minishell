/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:57:17 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/03 11:49:35 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_signals_heredoc(void)
{
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals_child(char *cmd)
{
	signal(SIGINT, ft_handler_child);
	if (ft_strncmp(cmd, "cat", 4) == 0)
		signal(SIGQUIT, ft_handler_child);
	else
		signal(SIGQUIT, SIG_IGN);
}

void	ft_signals(void)
{
	signal(SIGINT, ft_handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}
