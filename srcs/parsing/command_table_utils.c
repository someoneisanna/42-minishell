/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:47:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 14:43:27 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	**ft_add_redirections(t_token *first, t_type type);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

t_cmd	*ft_new_cmd(t_token *first, int n_args)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_get_args(first, n_args);
	new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	new_cmd->file_in = ft_add_redirections(first, T_FILE_IN);
	new_cmd->file_tr = ft_add_redirections(first, T_FILE_TR);
	new_cmd->file_ap = ft_add_redirections(first, T_FILE_AP);
	new_cmd->heredoc = ft_add_redirections(first, T_HEREDOC);
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

char	**ft_add_redirections(t_token *first, t_type type)
{
	int		i;
	int		n_redirs;
	char	**redirs;
	t_token	*curr;

	i = 0;
	n_redirs = ft_count_redir(first, type);
	redirs = (char **)ft_calloc(n_redirs + 1, sizeof(char *));
	if (!redirs)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type)
		{
			redirs[i] = ft_strdup(curr->content);
			i++;
		}
		curr = curr->next;
	}
	redirs[i] = NULL;
	return (redirs);
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
