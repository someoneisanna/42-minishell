/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:28:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/15 18:06:40 by ataboada         ###   ########.fr       */
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
		- ft_executer: this function will loop through the cmd_lst and execute
			each cmd, depending on the existence of pipes.
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
	t_cmd	*curr;

	curr = ms->cmd_lst;
	while (curr)
	{
		if (curr->next == NULL)
			ft_execute_only_cmd(ms, curr, curr->cmd);
		else
			ft_execute_mult_cmd(ms, curr, curr->cmd);
		curr = curr->next;
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
			ft_redir_handler(ms, curr);
		ft_execute_cmd(ms, curr, cmd);
		ft_close_fds(curr);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd)
{
	printf("executing piped %s\n", curr->cmd);
	(void)ms;
	(void)cmd;
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
		tmp = ft_strjoin(possible_paths[i], "/");
		possible_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!tmp || !possible_path)
			break ;
		if (access(possible_path, F_OK | X_OK) == 0)
			execve(possible_path, curr->args, ms->envp);
		free(possible_path);
		i++;
	}
	ft_perror(ms, E_CMD, YES);
}
