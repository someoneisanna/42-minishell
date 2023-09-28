/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:50:25 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/28 16:12:18 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handle_redir(t_minishell *ms, t_cmd *curr);
void	ft_close_fds(t_cmd *curr);
int		ft_handle_heredoc(t_minishell *ms, char *delimiter);
void	ft_create_heredoc(t_minishell *ms, char *delimiter);
char	*ft_expand_heredoc(t_minishell *ms, char *line);

/*
	This is where we keep the functions that handle redirections and heredocs.
	We have:
		- ft_redir_handler: this function will open the redirection files.
		- ft_close_fds: this function will close the file descriptors that were
			opened in ft_redir_handler.
		- ft_heredoc_handler: this function will handle the heredocs.
		- ft_heredoc_creator: this function will create the heredoc file.
		- ft_heredoc_expander: this function will expand the env variables that
			were in the heredoc.
*/

void	ft_handle_redir(t_minishell *ms, t_cmd *curr)
{
	if (curr->file_in)
		curr->fd_in = open(curr->file_in, O_RDONLY);
	if (curr->file_tr)
		curr->fd_out = open(curr->file_tr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (curr->heredoc)
		curr->fd_in = ft_handle_heredoc(ms, curr->heredoc);
	if (curr->file_ap)
		curr->fd_out = open(curr->file_ap, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (curr->fd_in < 0 || curr->fd_out < 0)
		exit (ft_perror(ms, E_FILE, YES));
	else
	{
		dup2(curr->fd_in, STDIN_FILENO);
		dup2(curr->fd_out, STDOUT_FILENO);
	}
}

void	ft_close_fds(t_cmd *curr)
{
	if (curr->fd_in > STDIN_FILENO)
		close(curr->fd_in);
	if (curr->fd_out > STDOUT_FILENO)
		close(curr->fd_out);
	curr->fd_in = STDIN_FILENO;
	curr->fd_out = STDOUT_FILENO;
}

int	ft_handle_heredoc(t_minishell *ms, char *delimiter)
{
	(void)ms;
	return (open(delimiter, O_RDONLY));
}

void	ft_create_heredoc(t_minishell *ms, char *delimiter)
{
	(void)ms;
	(void)delimiter;
}

char	*ft_expand_heredoc(t_minishell *ms, char *line)
{
	(void)ms;
	line = NULL;
	return (line);
}
