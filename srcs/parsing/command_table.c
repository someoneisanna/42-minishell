/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/30 12:49:44 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);

int	ft_command_table_creator(t_minishell *ms)
{
	t_token	*curr;

	curr = ms->token_lst;
	while (curr)
	{
		if (curr->type == T_OTHER)
			curr->type = T_COMMAND;
		else if (curr->type == T_REDIR_IN)
			curr->next->type = T_FILE_IN;
		else if (curr->type == T_REDIR_OUT)
			curr->next->type = T_FILE_TR;
		else if (curr->type == T_REDIR2_OUT)
			curr->next->type = T_FILE_AP;
		else if (curr->type == T_REDIR2_IN)
			curr->next->type = T_HEREDOC;
		else if (curr->type == T_PIPE)
			curr->next->type = T_COMMAND;
		curr = curr->next;
	}
	if (ft_command_table_helper(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	return (EXIT_SUCCESS);
}

int	ft_command_table_helper(t_minishell *ms)
{
	int		n_args;
	t_token	*curr;
	t_token	*first_cmd;

	n_args = 0;
	curr = ms->token_lst;
	while (curr)
	{
		if (curr->type == T_COMMAND || curr->type == T_EMPTY)
		{
			n_args = 0;
			first_cmd = curr;
			while (curr && (curr->type == T_COMMAND || curr->type == T_EMPTY))
			{
				n_args++;
				curr = curr->next;
			}
			if (n_args == 1 && ms->token_lst->type == T_EMPTY)
				return (EXIT_NO_CMD);
			ft_add_cmd_back(&ms->cmd_lst, ft_new_cmd(first_cmd, n_args));
		}
		else
			curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
