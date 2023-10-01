/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:28:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/30 17:56:12 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);

/*
	This is the main function of the execution part of the program.
	We have:
		- ft_executer: we will check for the existence of pipes and direct the
			program to the right function.
		- ft_execute_only_cmd: if there are no pipes, we will execute the cmd
			(cmd could be a builtin or external).
		- ft_execute_mult_cmd: if there are pipes, we will execute the piped
			cmds here.
		- ft_execute_cmd: we will check if the cmd is a builtin or not and
			direct it to the right function.
		- ft_execute_external: if the cmd is not a builtin, we will check if it
			is an executable file and execute it with execve.
*/

void	ft_executer(t_minishell *ms)
{
	int		n_pipes;
	t_cmd	*curr;

	curr = ms->cmd_lst;
	ms->n_pipes = ft_count_pipes(ms->cmd_lst);
	n_pipes = ms->n_pipes + 1;
	if (ms->n_pipes == 0)
		ft_execute_only_cmd(ms, curr, curr->cmd);
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
		while (n_pipes-- > 0)
			waitpid(ms->pid[n_pipes], NULL, 0);
	}
}

void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror(ms, E_FORK, YES);
	else if (pid == 0)
	{
		if (ft_cmd_has_redir(curr) == YES)
			ft_handle_redir(ms, curr);
		ft_execute_cmd(ms, curr, cmd);
		ft_close_fds(curr);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (curr->heredocs[0])
		waitpid(ms->pid_heredoc, NULL, 0);
	ms->pid[curr->index] = fork();
	if (ms->pid[curr->index] < 0)
		ft_perror(ms, E_FORK, YES);
	else if (ms->pid[curr->index] == 0)
	{
		if (ft_cmd_has_redir(curr) == YES)
			ft_handle_redir(ms, curr);
		ft_handle_pipes(ms, curr);
		ft_close_pipes(ms);
		ft_close_fds(curr);
		ft_execute_cmd(ms, curr, cmd);
	}
}

void	ft_execute_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ft_echo(ms, curr);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(ms, curr);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ft_pwd(ms, curr);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(ms, curr);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(ms, curr);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(ms, curr);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ft_exit(ms, curr);
	else
		ft_execute_external(ms, curr, cmd);
}

void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd)
{
	int		i;
	char	*tmp;
	char	*possible_path;
	char	**possible_paths;

	i = 0;
	possible_paths = ms->paths;
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
		free(possible_path);
		i++;
	}
	ft_perror(ms, E_CMD, YES);
}
