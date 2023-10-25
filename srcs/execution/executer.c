/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:28:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 16:10:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);

void ft_executer(t_minishell *ms)
{
	int		i;
	int		status;
	t_cmd	*curr;

	i = 0;
	status = 0;
	curr = ms->cmd_lst;
	ms->n_pipes = ft_count_pipes(ms->cmd_lst);
	if (ms->n_pipes == 0)
	{
		if (ft_not_forkable(ms) == FALSE)
			ft_execute_only_cmd(ms, curr, curr->cmd);
		if (ft_strncmp(ms->cmd_lst->cmd, "exit", 5) == 0 && is_there_redirections(ms) == TRUE)//PORQUE E QUE ISTO ESTA AQUI??? :D
			exit(0); // alterar para g_exit_status???
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
		{
			waitpid(ms->pid[i++], &status, 0);
			ft_signals();
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}

void ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (ft_strncmp(cmd, "cat", 4) == 0)
		ft_signals_child(cmd);
	pid = fork();
	if (pid < 0)
		ft_perror(ms, E_FORK, YES);
	else if (pid == 0)
	{
		ft_unsetable(ms, cmd);
		if (ft_cmd_has_redir(curr) == TRUE)
			ft_handle_redir(ms, curr);
		ft_execute_cmd(ms, curr, cmd);
		ft_close_fds(curr);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_signals();
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (curr->heredoc[0])
	{
		ft_signals_heredoc();
		waitpid(ms->pid_heredoc, NULL, 0);
	}
	if (ft_strncmp(cmd, "cat", 4) == 0)
		ft_signals_child(cmd);
	ms->pid[curr->index] = fork();
	if (ms->pid[curr->index] < 0)
		ft_perror(ms, E_FORK, YES);
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
}

void ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(ms);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(ms);
	else if (ft_strncmp(cmd, "env", 4) == 0 && ft_get_paths(ms->env_lst))
		ft_env(ms);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(ms);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(ms);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(ms);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(ms);
	else
		ft_execute_external(ms, curr, cmd);
}

void ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd)
{
	int		i;
	char	*tmp;
	char	*possible_path;
	char	**possible_paths;

	i = 0;
	possible_paths = ft_get_paths(ms->env_lst);
	while (possible_paths[i])
	{
		if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
			possible_path = ft_strdup(cmd);
		else
		{
			tmp = ft_strjoin(possible_paths[i], "/");
			possible_path = ft_strjoin(tmp, cmd);
			free(tmp);
			if (!tmp || !possible_path)
				break ;
		}
		if (access(possible_path, F_OK | X_OK) == 0)
			execve(possible_path, curr->args, ms->envp);
		else
			g_exit_status = 127;
		free(possible_path);
		i++;
	}
	ft_perror(ms, E_CMD, YES);
}
