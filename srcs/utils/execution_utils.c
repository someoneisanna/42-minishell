/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/21 09:57:30 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_cmd_has_redir(t_cmd *cmd);
int		ft_count_pipes(t_cmd *cmd_lst);

int	ft_cmd_has_redir(t_cmd *cmd)
{
	if (cmd->file_in)
		return (YES);
	if (cmd->file_tr)
		return (YES);
	if (cmd->heredoc)
		return (YES);
	if (cmd->file_ap)
		return (YES);
	return (NO);
}

int	ft_count_pipes(t_cmd *cmd_lst)
{
	int		n_cmds;
	int		n_pipes;
	t_cmd	*curr;

	n_cmds = 0;
	curr = cmd_lst;
	while (curr)
	{
		n_cmds++;
		curr = curr->next;
	}
	if (n_cmds < 2)
		n_pipes = 0;
	else
		n_pipes = n_cmds - 1;
	return (n_pipes);
}
