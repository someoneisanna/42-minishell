/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:50:25 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/05 16:54:24 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_cmd_has_redir(t_cmd *curr);
void	ft_handle_redir(t_minishell *m, t_cmd *c);
int		ft_open_fd(t_minishell *m, t_cmd *c, char *filename, t_type filetype);
void	ft_close_fds(t_cmd *curr);

int	ft_cmd_has_redir(t_cmd *curr)
{
	if (curr->f_redin[0])
		return (YES);
	if (curr->f_redout[0])
		return (YES);
	return (NO);
}

void	ft_handle_redir(t_minishell *m, t_cmd *c)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	while (c->f_redin[i])
	{
		if (c->t_redin[i] == T_FILE_IN)
			c->fd_in = ft_open_fd(m, c, c->f_redin[i], c->t_redin[i]);
		else if (c->t_redin[i] == T_HEREDOC)
			c->fd_in = ft_handle_heredoc(m, c->f_redin[i]);
		i++;
	}
	i = 0;
	while (c->f_redout[i])
	{
		c->fd_out = ft_open_fd(m, c, c->f_redout[i], c->t_redout[i]);
		i++;
	}
	if (ft_is_forkable(m, NO) == TRUE)
	{
		dup2(c->fd_in, STDIN_FILENO);
		dup2(c->fd_out, STDOUT_FILENO);
	}
}

int	ft_open_fd(t_minishell *m, t_cmd *c, char *filename, t_type filetype)
{
	int		fd;

	fd = 0;
	if (filetype == T_FILE_IN)
		fd = open(filename, O_RDONLY);
	else if (filetype == T_FILE_TR)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (filetype == T_FILE_AP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		g_exit_status = 1;
		if (ft_strlen(filename) > 0)
			printf("minishell: %s: %s: %s\n", c->cmd, filename, E_FILE);
		else
			printf("minishell: ambiguous redirect\n");
		if (ft_is_forkable(m, NO) == TRUE)
			ft_perror(m, NULL, YES, NULL);
		else if (ft_is_forkable(m, NO) == FALSE)
			ft_perror(m, NULL, NO, NULL);
	}
	return (fd);
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
