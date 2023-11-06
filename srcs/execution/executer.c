/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:28:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 14:03:26 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
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
			ft_execute_mult_cmd(ms, curr, curr->cmd);
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

	if (ft_strcmp(cmd, "cat") == 0)
		ft_signals_child(cmd);
	pid = fork();
	if (pid < 0)
		ft_perror(ms, E_FORK, YES, NULL);
	else if (pid == 0)
	{
		ft_unsetable(ms, cmd);
		if (ft_cmd_has_redir(curr) == TRUE)
			ft_handle_redir(ms, curr);
		ft_execute_cmd(ms, curr, cmd);
		ft_close_fds(curr);
	}
	else
		ft_waitpid_handler(ms, 0, pid, NO);
}

void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (ft_strncmp(cmd, "cat", 4) == 0)
		ft_signals_child(cmd);
	ms->pid[curr->index] = fork();
	if (ms->pid[curr->index] < 0)
		ft_perror(ms, E_FORK, YES, NULL);
	else if (ms->pid[curr->index] == 0)
	{
		ft_unsetable(ms, cmd);
		if (ft_cmd_has_redir(curr) == YES)
			ft_handle_redir(ms, curr);
		ft_handle_pipes(ms, curr);
		ft_close_pipes(ms);
		ft_close_fds(curr);
		ft_execute_cmd(ms, curr, cmd);
	}
	if (curr->has_heredoc == YES)
	{
		ft_signals_heredoc();
		waitpid(-1, NULL, 0);
	}
}

void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	char	**path_array;

	path_array = ft_get_paths(ms->env_lst);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(ms, curr);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(curr);
	else if (ft_strncmp(cmd, "env", 4) == 0 && path_array)
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
	ft_free_str_array(path_array);
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
	ft_perror(ms, E_CMD, YES, cmd);
}
