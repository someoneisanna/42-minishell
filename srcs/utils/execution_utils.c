/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/10 14:40:06 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_is_forkable(t_minishell *ms, int execution_flag);
void	ft_set_cmd_index(t_minishell *ms);
void	ft_waitpid_handler(t_minishell *ms, int i, pid_t pid, int exec_flag);
char	*ft_find_path(char *cmd, char *possible_paths);
void	ft_execute_mult_cmd_helper(t_minishell *ms, t_cmd *curr, int flag);

int	ft_is_forkable(t_minishell *ms, int execution_flag)
{
	if (!ft_strcmp(ms->cmd_lst->cmd, "cd")
		|| !ft_strcmp(ms->cmd_lst->cmd, "exit")
		|| !ft_strcmp(ms->cmd_lst->cmd, "export")
		|| !ft_strcmp(ms->cmd_lst->cmd, "unset"))
	{
		if (execution_flag == YES)
		{
			ft_handle_redir(ms, ms->cmd_lst);
			if (ms->file_error == NO)
				ft_execute_cmd(ms, ms->cmd_lst, ms->cmd_lst->cmd);
		}
		return (FALSE);
	}
	else
		return (TRUE);
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

void	ft_waitpid_handler(t_minishell *ms, int i, pid_t pid, int exec_flag)
{
	int	status;

	status = 0;
	if (exec_flag == YES)
		waitpid(ms->pid[i++], &status, 0);
	else if (exec_flag == NO)
		waitpid(pid, &status, 0);
	ft_signals();
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status) && !ms->core_dump)
			printf("Quit (core dumped)\n");
		ms->core_dump = YES;
		g_exit_status = 128 + WTERMSIG(status);
	}
}

char	*ft_find_path(char *cmd, char *possible_paths)
{
	char	*tmp;
	char	*possible_path;

	tmp = NULL;
	if (!ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "./", 2))
		possible_path = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin(possible_paths, "/");
		possible_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!tmp)
			return (NULL);
	}
	return (possible_path);
}

void	ft_execute_mult_cmd_helper(t_minishell *ms, t_cmd *curr, int flag)
{
	if (flag == 0)
	{
		if (curr->has_heredoc == NO)
			signal(SIGQUIT, ft_handler_child);
		else
			signal(SIGQUIT, SIG_IGN);
	}
	if (flag == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (curr->has_heredoc == YES)
		{
			ft_free_heredoc(0, ms);
			signal(SIGINT, ft_handler_heredoc);
			signal(SIGQUIT, SIG_IGN);
		}
		ft_unsetable(ms, curr->cmd);
	}
}
