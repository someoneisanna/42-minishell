/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:28:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/10 14:28:56 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
int		ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);

void	ft_executer(t_minishell *ms)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = ms->cmd_lst;
	ms->n_pipes = ft_count_pipes(ms->cmd_lst);
	if (ms->n_pipes == 0)
	{
		if (ft_is_forkable(ms, YES) == TRUE)
			ft_execute_only_cmd(ms, curr, curr->cmd);
	}
	else
	{
		ft_set_cmd_index(ms);
		ft_open_pipes(ms);
		while (curr)
		{
			if (ft_execute_mult_cmd(ms, curr, curr->cmd) == 42)
				return ;
			curr = curr->next;
		}
		ft_close_pipes(ms);
		while (i < ms->n_pipes + 1)
			ft_waitpid_handler(ms, i++, 0, YES);
	}
}

void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (curr->has_heredoc == NO)
		signal(SIGQUIT, ft_handler_child);
	else
		signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		ft_perror(ms, E_FORK, YES, NULL);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (curr->has_heredoc == YES)
		{
			ft_free_heredoc(0, ms);
			signal(SIGINT, ft_handler_heredoc);
			signal(SIGQUIT, SIG_IGN);
		}
		ft_unsetable(ms, cmd);
		if (ft_cmd_has_redir(curr) == TRUE)
			ft_handle_redir(ms, curr);
		ft_execute_cmd(ms, curr, cmd);
		ft_close_fds(curr);
	}
	else
		ft_waitpid_handler(ms, status, pid, NO);
}

int	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	int	status;

	status = 0;
	ft_execute_mult_cmd_helper(ms, curr, 0);
	ms->pid[curr->index] = fork();
	if (ms->pid[curr->index] < 0)
		ft_perror(ms, E_FORK, YES, NULL);
	else if (ms->pid[curr->index] == 0)
	{
		ft_execute_mult_cmd_helper(ms, curr, 1);
		if (ft_cmd_has_redir(curr) == YES)
			ft_handle_redir(ms, curr);
		ft_handle_pipes(ms, curr);
		ft_close_pipes(ms);
		ft_close_fds(curr);
		ft_execute_cmd(ms, curr, cmd);
	}
	if (curr->has_heredoc == YES)
	{
		while (waitpid(-1, &status, WNOHANG) == 0)
			;
		if (WIFSIGNALED(status))
			return (42);
	}
	return (0);
}

void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(ms, curr);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(ms, curr);
	else if (ft_strncmp(cmd, "env", 4) == 0 && ft_find_env(ms->env_lst, "PATH"))
		ft_env(ms, curr);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(ms, curr);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(ms, curr);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(ms, curr);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(ms, curr);
	else
		ft_execute_external(ms, curr, cmd);
}

void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd)
{
	int		i;
	char	*possible_path;
	char	**possible_paths;

	i = 0;
	possible_paths = ft_get_paths(ms->env_lst);
	if (!possible_paths)
		ft_perror(ms, NULL, YES, NULL);
	while (possible_paths[i])
	{
		possible_path = ft_find_path(cmd, possible_paths[i]);
		if (!possible_path)
			ft_perror(ms, E_CMD, YES, cmd);
		if (access(possible_path, F_OK | X_OK) == 0)
			execve(possible_path, curr->args, ms->envp);
		else
			g_exit_status = 127;
		free(possible_path);
		i++;
	}
	ft_free_str_array(possible_paths);
	if (ms->n_pipes > 0)
		ft_free_pipes(ms);
	ft_perror(ms, E_CMD, YES, cmd);
}
