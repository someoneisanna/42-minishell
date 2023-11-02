/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:58:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/29 18:08:27 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_open_pipes(t_minishell *ms);
void	ft_handle_pipes(t_minishell *ms, t_cmd *curr);
void	ft_close_pipes(t_minishell *ms);

int	ft_count_pipes(t_cmd *cmd_lst)
{
	int		n_cmds;
	int		n_pipes;
	t_cmd	*curr;

	n_cmds = 0;
	curr = cmd_lst;
	while (curr)
	{
		n_cmds++;
		curr = curr->next;
	}
	if (n_cmds < 2)
		n_pipes = 0;
	else
		n_pipes = n_cmds - 1;
	return (n_pipes);
}

void	ft_open_pipes(t_minishell *ms)
{
	int	i;

	i = 0;
	if (ms->n_pipes == 0)
		return ;
	ms->pid = (pid_t *)ft_calloc(sizeof(pid_t), ms->n_pipes + 1);
	if (!ms->pid)
		ft_perror(ms, E_MALLOC, NO, NULL);
	if (ms->n_pipes == 0)
		return ;
	ms->pipe_fd = (int **)ft_calloc(sizeof(int *), ms->n_pipes);
	if (!ms->pipe_fd)
		ft_perror(ms, E_MALLOC, NO, NULL);
	while (i < ms->n_pipes)
	{
		ms->pipe_fd[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!ms->pipe_fd[i])
			ft_perror(ms, E_MALLOC, NO, NULL);
		if (pipe(ms->pipe_fd[i]) < 0)
			ft_perror(ms, E_PIPE, NO, NULL);
		i++;
	}
}

void	ft_handle_pipes(t_minishell *ms, t_cmd *curr)
{
	if (curr->index == 0)
	{
		dup2(curr->fd_in, STDIN_FILENO);
		dup2(ms->pipe_fd[curr->index][1], STDOUT_FILENO);
	}
	else if (curr->next == NULL || curr->fd_out > STDOUT_FILENO)
	{
		dup2(ms->pipe_fd[curr->index - 1][0], STDIN_FILENO);
		dup2(curr->fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(ms->pipe_fd[curr->index - 1][0], STDIN_FILENO);
		dup2(ms->pipe_fd[curr->index][1], STDOUT_FILENO);
	}
	if (curr->fd_in > STDIN_FILENO)
		dup2(curr->fd_in, STDIN_FILENO);
	if (curr->fd_out > STDOUT_FILENO)
		dup2(curr->fd_out, STDOUT_FILENO);
}

void	ft_close_pipes(t_minishell *ms)
{
	int	i;

	i = 0;
	while (i < ms->n_pipes)
	{
		close(ms->pipe_fd[i][0]);
		close(ms->pipe_fd[i][1]);
		i++;
	}
}
