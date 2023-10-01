/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 16:26:17 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);

/*
	Here is where we build the final step of the parser, the command table. The command table was created thinking about the execution of the program, so it has a format that will help us use the execve function later.

	First step: update the tokenizer, separating the T_OTHER tokens into T_COMMAND, T_FILE_IN, T_FILE_TRUNC, T_FILE_APPEND and T_DELIMITER.
	For example:
		input: ls -l | wc -l > a.txt
		|--------------------------------|
		| token | content |     type     |
		|-------|---------|--------------|
		|   1   |   ls    | T_COMMAND    |
		|   2   |   -l    | T_COMMAND    |
		|   3   |    |    | T_PIPE       |
		|   4   |   wc    | T_COMMAND    |
		|   5   |   -l    | T_COMMAND    |
		|   6   |    >    | T_REDIR_OUT  |
		|   7   |  a.txt  | T_FILE_TRUNC |
		|_______|_________|______________|

	Second step: separate it all into commands.
	For example:
		input: ls - l > a.txt | sort << A << B > b.txt
		|--------------------------------|
		| cmd_number |    1    |    2    |
		|------------|---------|---------|
		|    cmd     |    ls   |  sort   |
		|    args    | ls, -l  |  sort   |
		|  file_in   |   NULL  |  NULL   |
		|  file_tr   |  a.txt  |  b.txt  |
		|  file_ap   |   NULL  |  NULL   |
		|  heredocs  |   NULL  |  A, B   |
		|____________|_________|_________|

	Remember: if the expanded variable doesn't exist, it will be called T_EMPTY, and it should be ignored.
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
			ft_add_cmd_back(&ms->cmd_lst, ft_new_cmd(ms, first_cmd, n_args));
		}
		else
			curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
