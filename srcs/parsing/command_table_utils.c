/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:47:33 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/07 10:04:06 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	**ft_add_files(t_token *first, t_type type1, t_type type2);
int		*ft_add_types(t_token *first, t_type type1, t_type type2);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

/*
	Here we have the functions that will help us build the command table.

	ft_new_command will allocate memory to each new command node and fill it
	with the information we need to execute it.

	ft_get_args will get the arguments of each command.

	For example, ls -l -a will have as args: ["ls", "-l", "-a"].

	ft_add_files will get the files of each command.

	For example, cat < a.txt << a > b.txt | grep A | wc -l >> c.txt
	will have as files: ["a.txt", "a", b.txt", "c.txt"].

	They will be divided in two char **, one for input files and one for output
	files.

	So, for example, cat < a.txt << a > b.txt | grep A | wc -l >> c.txt will be:
		* input files: f_redin: ["a.txt", "a"]
		* output files: f_redout: ["b.txt", "c.txt"]

	ft_add_types will get the types of each file, so that we know if we are
	dealing with T_FILE_IN or T_HEREDOC in the case of input files, or with
	T_FILE_TR or T_FILE_AP in the case of output files.

	So, for example, cat < a.txt << a > b.txt | grep A | wc -l >> c.txt will be:
		* input files: t_redin: [T_FILE_IN, T_HEREDOC]
		* output files: t_redout: [T_FILE_TR, T_FILE_AP]

	Now, we have all the information about redirections, and can work with them
	in the execution part.

	ft_add_cmd_back will add the new command to the back of the command table.
*/

t_cmd	*ft_new_cmd(t_token *first, int n_args)
{
	t_cmd	*new_cmd;
	t_token	*cur_tkn;

	cur_tkn = first;
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_get_args(first, n_args);
	new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	new_cmd->f_redin = ft_add_files(first, T_FILE_IN, T_HEREDOC);
	new_cmd->f_redout = ft_add_files(first, T_FILE_TR, T_FILE_AP);
	new_cmd->t_redin = ft_add_types(first, T_FILE_IN, T_HEREDOC);
	new_cmd->t_redout = ft_add_types(first, T_FILE_TR, T_FILE_AP);
	while (cur_tkn && cur_tkn->type != T_PIPE)
	{
		if (cur_tkn->type == T_REDIR2_IN)
			new_cmd->has_heredoc = YES;
		cur_tkn = cur_tkn->next;
	}
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

char	**ft_add_files(t_token *first, t_type type1, t_type type2)
{
	int		i;
	int		n_redirs;
	char	**redirs;
	t_token	*curr;

	i = 0;
	n_redirs = ft_count_redir(first, type1, type2);
	redirs = (char **)ft_calloc(n_redirs + 1, sizeof(char *));
	if (!redirs)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type1 || curr->type == type2)
		{
			redirs[i] = ft_strdup(curr->content);
			i++;
		}
		curr = curr->next;
	}
	redirs[i] = NULL;
	return (redirs);
}

int	*ft_add_types(t_token *first, t_type type1, t_type type2)
{
	int		i;
	int		n_redirs;
	int		*types;
	t_token	*curr;

	i = 0;
	n_redirs = ft_count_redir(first, type1, type2);
	types = (int *)ft_calloc(n_redirs + 1, sizeof(int));
	if (!types)
		return (NULL);
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type1 || curr->type == type2)
		{
			types[i] = curr->type;
			i++;
		}
		curr = curr->next;
	}
	types[i] = 0;
	return (types);
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
