/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:47:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/19 19:06:40 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	*ft_add_redirections(t_token *first, int n_args, t_type type);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);
void	ft_free_cmd_lst(t_cmd **cmd_table);

/*
	Here are the auxiliary functions for the command table. Here are the usual ft_new, ft_add_back and ft_free, but also some functions to get the arguments and redirections properly.
*/

t_cmd	*ft_new_cmd(t_token *first, int n_args)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_get_args(first, n_args);
	new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	new_cmd->file_in = ft_add_redirections(first, n_args, T_FILE_IN);
	new_cmd->file_tr = ft_add_redirections(first, n_args, T_FILE_TRUNC);
	new_cmd->heredoc = ft_add_redirections(first, n_args, T_DELIMITER);
	new_cmd->file_ap = ft_add_redirections(first, n_args, T_FILE_APPEND);
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->index = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

char	**ft_get_args(t_token *first, int n_args)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (i < n_args)
	{
		args[i] = ft_strdup(first->content);
		i++;
		first = first->next;
	}
	args[i] = NULL;
	return (args);
}

char	*ft_add_redirections(t_token *first, int n_args, t_type type)
{
	(void)n_args;
	(void)type;
	t_token	*curr;

	curr = first;
	while (curr && curr->next)
		curr = curr->next;
	while (curr && curr->type != type)
		curr = curr->prev;
	if (curr)
		return (ft_strdup(curr->content));
	return (NULL);
}

void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*cmd_table)
	{
		*cmd_table = new_cmd;
		return ;
	}
	current = *cmd_table;
	while (current && current->next)
		current = current->next;
	current->next = new_cmd;
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
		free(current->heredoc);
		free(current->file_ap);
		free(current);
		current = next;
	}
	*cmd_table = NULL;
}
