/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:50:25 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/02 10:25:18 by ataboada         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (curr->file_in[i])
		curr->fd_in = ft_perror_fd(ms, curr->file_in[i++], T_FILE_IN);
	i = 0;
	while (curr->file_tr[i])
		curr->fd_out = ft_perror_fd(ms, curr->file_tr[i++], T_FILE_TRUNC);
	i = 0;
	while (curr->file_ap[i])
		curr->fd_out = ft_perror_fd(ms, curr->file_ap[i++], T_FILE_APPEND);
	i = 0;
	while (curr->heredoc[i])
		curr->fd_in = ft_handle_heredoc(ms, curr->heredoc[i++]);
	dup2(curr->fd_in, STDIN_FILENO);
	dup2(curr->fd_out, STDOUT_FILENO);
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
	ms->pid_heredoc = fork();
	if (ms->pid_heredoc < 0)
		ft_perror(ms, E_FORK, YES);
	else if (ms->pid_heredoc == 0)
		ft_create_heredoc(ms, delimiter);
	else
		waitpid(ms->pid_heredoc, NULL, 0);
	return (open(".heredoc", O_RDONLY));
}

void	ft_create_heredoc(t_minishell *ms, char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_perror(ms, E_HEREDOC, YES);
			break ;
		}
		if (line && ft_strncmp(line, delimiter, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break ;
		}
		line = ft_expand_heredoc(ms, line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	if (ms->n_pipes > 0)
		ft_free_pipes(ms);
	ft_free_all(ms, YES);
}

char	*ft_expand_heredoc(t_minishell *ms, char *line)
{
	char	*tmp;
	char	*key;
	char	*value;
	char	*heredoc_expanded;

	heredoc_expanded = ft_strdup(line);
	while (ft_strchr(heredoc_expanded, '$') != NULL)
	{
		key = ft_get_key(heredoc_expanded);
		if (ft_strncmp(key, "$?", 3) == 0)
			value = ft_itoa(42); //create a exit status variable
		else
			value = ft_get_env_value(&ms->env_lst, key);
		tmp = heredoc_expanded;
		heredoc_expanded = ft_replace_content(heredoc_expanded, key, value);
		free(tmp);
		free(key);
		free(value);
	}
	return (heredoc_expanded);
}
