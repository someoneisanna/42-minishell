/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/07 18:15:04 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_command_table_creator(t_minishell *ms);
void	ft_command_table_helper(t_minishell *ms);

/*
	This is where the command table will be created.
	It will be a linked list of t_cmd structures. Each t_cmd structure will have a the command name, its arguments and its associated redirections.
*/

void	ft_command_table_creator(t_minishell *ms)
{
	t_token	*curr;

	curr = ms->token;
	while (curr)
	{
		if (ft_is_cmd_or_file(curr->type) == YES)
			curr->type = T_COMMAND;
		else if (curr->type == T_REDIR_IN)
			curr->next->type = T_FILE_IN;
		else if (curr->type == T_REDIR_OUT)
			curr->next->type = T_FILE_TRUNC;
		else if (curr->type == T_REDIR2_OUT)
			curr->next->type = T_FILE_APPEND;
		else if (curr->type == T_REDIR2_IN)
			curr->next->type = T_DELIMITER;
		else if (curr->type == T_PIPE)
			curr->next->type = T_COMMAND;
		curr = curr->next;
	}
	ft_command_table_helper(ms);
}

void	ft_command_table_helper(t_minishell *ms)
{
	int		n_args;
	t_token	*curr;
	t_token	*first_cmd;

	n_args = 0;
	curr = ms->token;
	while (curr)
	{
		if (curr->type == T_COMMAND)
		{
			n_args = 0;
			first_cmd = curr;
			while (curr && curr->type == T_COMMAND)
			{
				n_args++;
				curr = curr->next;
			}
			ft_add_cmd_back(&ms->cmd_table, ft_new_cmd(first_cmd, n_args));
		}
		else
			curr = curr->next;
	}
}
