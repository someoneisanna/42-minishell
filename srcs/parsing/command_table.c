/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:49:32 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/07 00:02:01 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);

/*
	This is where we will create the command table.

	We will create the command table by iterating through the token_lst and
	creating a new cmd_lst, according to the type of the token.

	ft_command_table_creator:
		* we will iterate through the token_lst and separate the T_OTHER tokens
		into T_COMMAND, T_FILE_IN, T_FILE_TR, T_FILE_AP, T_HEREDOC.
		* if we have:
			T_OTHER T_REDIR_IN T_OTHER T_PIPE T_OTHER T_REDIR_OUT,
		* we can predict that we have:
			COMMAND FILE_IN | COMMAND FILE_TR

	So, for the following command, the token list will become:
		cat < a.txt << a > b.txt | grep A | wc -l >> c.txt
		|------------------------------------------------|
		| token		| type		  | content				 |
		|------------------------------------------------|
		| cat		| T_COMMAND	  | cat					 |
		| <			| T_REDIR_IN  | <					 |
		| a.txt		| T_FILE_IN	  | a.txt				 |
		| <<		| T_HEREDOC	  | <<				 	 |
		| a			| T_HEREDOC	  | a				 	 |
		| >			| T_REDIR_OUT | >					 |
		| b.txt		| T_FILE_TR	  | b.txt				 |
		| |			| T_PIPE	  | |					 |
		| grep		| T_COMMAND	  | grep				 |
		| A			| T_COMMAND	  | A					 |
		| |			| T_PIPE	  | |					 |
		| wc		| T_COMMAND	  | wc					 |
		| -l		| T_COMMAND	  | -l					 |
		| >>		| T_REDIR2_OUT| >>					 |
		| c.txt		| T_FILE_AP	  | c.txt				 |
		|------------------------------------------------|

	After that, we will iterate through the token_lst again and create the
	cmd_lst, according to the type of the token.

	The cmd_lst is a list of commands, each command being a node. Each node has
	the following attributes:
		* cmd: the command itself.
		* args: the arguments of the command.
		* f_redin: the file to redirect the input.
		* f_redout: the file to redirect the output.
		* t_redin: the type of the input redirection.
		* t_redout: the type of the output redirection.
		* has_heredoc: if the command has a heredoc.
		* fd_in: the file descriptor of the input.
		* fd_out: the file descriptor of the output.
		* index: the index of the command in the command table.
		* next: the next command.

	The commands will be found according to pipes.

	If you have no pipes and T_COMMAND T_COMMAND T_REDIR_IN T_FILE_IN, you know
	that it will probably be a command like: ls -l < a.txt. So, we will create
	a command with the following attributes:
		* cmd: ls
		* args: ls, -l
		* f_redin: a.txt
		* f_redout: NULL
		* t_redin: T_FILE_IN
		* t_redout: NULL
		* has_heredoc: NO
		* fd_in: 0
		* fd_out: 1
		* index: 0
		* next: NULL

	A command like cat < a.txt << a > b.txt | grep A | wc -l >> c.txt will be:

	|------------------------------------------------------------------------|
	| cmd | args	| f_redin | f_redout | t_redin  | t_redout | has_heredoc |
	|------------------------------------------------------------------------|
	| cat | cat		| a.txt	  | NULL	 | T_FILE_IN| NULL	   | NO			 |
	| grep| grep A	| NULL	  | NULL	 | NULL	    | NULL	   | NO			 |
	| wc  | wc -l	| NULL	  | c.txt	 | NULL	    | T_FILE_AP| NO			 |
	|------------------------------------------------------------------------|
*/

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
