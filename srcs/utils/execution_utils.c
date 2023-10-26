/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 15:24:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_cmd_has_redir(t_cmd *cmd);
int		ft_open_fd(t_minishell *ms, char *filename, t_type file_type);
int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_set_cmd_index(t_minishell *ms);

int	ft_cmd_has_redir(t_cmd *cmd)
{
	if (cmd->file_in[0])
		return (YES);
	if (cmd->file_tr[0])
		return (YES);
	if (cmd->heredoc[0])
		return (YES);
	if (cmd->file_ap[0])
		return (YES);
	return (NO);
}

int	ft_open_fd(t_minishell *ms, char *filename, t_type file_type)
{
	int	fd;

	fd = 0;
	if (file_type == T_FILE_IN)
		fd = open(filename, O_RDONLY);
	else if (file_type == T_FILE_TR)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file_type == T_FILE_AP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_perror(ms, E_FILE, YES, filename);
	return (fd);
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

void	ft_set_cmd_index(t_minishell *ms)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = ms->cmd_lst;
	while (curr)
	{
		curr->index = i;
		i++;
		curr = curr->next;
	}
}
