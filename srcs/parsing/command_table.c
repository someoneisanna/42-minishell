/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/30 10:13:26 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);
void	ft_free_cmd_lst(t_cmd **cmd_table);

/*
	This is where the command table will be created.
	It will be a linked list of t_cmd structures. Each t_cmd structure will have the command name, its arguments and its associated redirections.
	We will first separate our T_OTHER tokens into T_COMMAND and T_FILE tokens.
	Then, we will create the command table.
	Remember: if the expanded variable doesn't exist, it will be called T_EMPTY.
*/

int	ft_command_table_creator(t_minishell *ms)
{
	t_token	*curr;

	curr = ms->token_lst;
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
	if (ft_command_table_helper(ms) == ERROR_FOUND)
		return (EXIT_FAILURE);
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
				return (EXIT_FAILURE);
			ft_add_cmd_back(&ms->cmd_lst, ft_new_cmd(ms, first_cmd, n_args));
		}
		else
			curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_free_cmd_lst(t_cmd **cmd_table)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!*cmd_table)
		return ;
	current = *cmd_table;
	while (current)
	{
		next = current->next;
		ft_free_str_array(current->args);
		free(current->cmd);
		free(current->file_in);
		free(current->file_tr);
		free(current->file_ap);
		ft_free_str_array(current->heredoc);
		free(current);
		current = next;
	}
	*cmd_table = NULL;
}
