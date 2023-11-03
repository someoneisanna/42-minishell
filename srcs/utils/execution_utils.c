/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/03 14:57:47 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_is_forkable(t_minishell *ms, int execution_flag);
void	ft_set_cmd_index(t_minishell *ms);
void	ft_waitpid_handler(t_minishell *ms, int i, pid_t pid, int exec_flag);
void	ft_unsetable(t_minishell *ms, char *cmd);
char	*ft_find_path(char *cmd, char *possible_paths);

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
			if (g_exit_status == 0)
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
		g_exit_status = 128 + WTERMSIG(status);
}

void	ft_unsetable(t_minishell *ms, char *cmd)
{
	char	**path_array;

	if (ft_strncmp(cmd, "echo", 5) == 0)
		return ;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return ;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return ;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return ;
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return ;
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return ;
	path_array = ft_get_paths(ms->env_lst);
	if (!path_array)
	{
		printf("minishel: %s: no such file or directory\n", cmd);
		g_exit_status = 127;
	}
	ft_free_str_array(path_array);
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
