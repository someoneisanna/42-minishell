/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:47:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 16:27:42 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(t_minishell *ms, t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	*ft_add_redirections(t_minishell *ms, t_token *first, t_type type);
char	**ft_add_heredocs(t_token *first);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

/*
	Here are the auxiliary functions for the command table. Here are the usual ft_new and ft_add_back, but also some functions to get the arguments and redirections properly.
	We have:
		- ft_new_cmd: this function will create a new command.
		- ft_get_args: this function will get the arguments of the command (for
			example, if your input is ls -l -a, it will be: ls, -l, -a, NULL)
		- ft_add_redirections: this function will get the redirections of the
			command. It looks confusing, but it needs to be like this because it has to handle cases like: ls > file1 > file2 > file3, in which each file has to be opened, but only the last one will be used as the STDOUT.
		- ft_add_cmd_back: this function will add the cmd to the command table.
*/

t_cmd	*ft_new_cmd(t_minishell *ms, t_token *first, int n_args)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_get_args(first, n_args);
	new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	new_cmd->file_in = ft_add_redirections(ms, first, T_FILE_IN);
	new_cmd->file_tr = ft_add_redirections(ms, first, T_FILE_TRUNC);
	new_cmd->file_ap = ft_add_redirections(ms, first, T_FILE_APPEND);
	new_cmd->heredocs = ft_add_heredocs(first);
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->index = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

char	**ft_get_args(t_token *first, int n_args)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	args = (char **)ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (i < n_args)
	{
		if (first->type == T_COMMAND)
		{
			args[j] = ft_strdup(first->content);
			j++;
		}
		i++;
		first = first->next;
	}
	args[i] = NULL;
	return (args);
}

char	*ft_add_redirections(t_minishell *ms, t_token *first, t_type type)
{
	t_token	*curr;
	t_token *last;

	curr = first;
	last = NULL;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type)
		{
			if (ft_perror_fd(ms, curr->content, type) != 0)
				break ;
		}
		last = curr;
		curr = curr->next;
	}
	while (last->prev && last->type != type && last->type != T_PIPE)
		last = last->prev;
	if (last && last->type == type)
		return (ft_strdup(last->content));
	return (NULL);
}

char	**ft_add_heredocs(t_token *first)
{
	int		i;
	int		n_heredocs;
	char	**heredocs;
	t_token	*curr;

	i = 0;
	n_heredocs = ft_count_heredocs(first);
	heredocs = (char **)ft_calloc(n_heredocs + 1, sizeof(char *));
	if (!heredocs)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_DELIMITER)
		{
			heredocs[i] = ft_strdup(curr->content);
			i++;
		}
		curr = curr->next;
	}
	heredocs[i] = NULL;
	return (heredocs);
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
