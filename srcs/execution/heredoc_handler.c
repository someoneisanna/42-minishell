/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:02:44 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/03 14:18:36 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_handle_heredoc(t_minishell *ms, char *delimiter);
void	ft_create_heredoc(t_minishell *ms, char *delimiter);
char	*ft_expand_heredoc(t_minishell *ms, char *line);

int	ft_handle_heredoc(t_minishell *ms, char *delimiter)
{
	ms->pid_heredoc = fork();
	if (ms->pid_heredoc < 0)
		ft_perror(ms, E_FORK, YES, NULL);
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
			ft_perror(ms, E_HEREDOC, YES, delimiter);
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
			value = ft_itoa(g_exit_status);
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
