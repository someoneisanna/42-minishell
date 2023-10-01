/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:58:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 16:37:38 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_pipes(t_minishell *ms);
void	ft_handle_pipes(t_minishell *ms, t_cmd *curr);
void	ft_close_pipes(t_minishell *ms);

/*
	Here we have the functions that help us handle the pipes.
	We have:
		- ft_open_pipes: this function will create and allocate memory for
			the pipes, as well as allocate memory for the fork pids.
		- ft_pipes_handler: this function is the responsible to handle the STDIN
			and STDOUT of each command, depending on each being the first
			command, last command, or middle command (pipe before and after it).
		- ft_close_pipes: this function will close all the pipes that were
			previously opened.

	To understand the pipes_handler function a little better, here is an example:

		input: ls -l | grep a | wc -l > a.txt
		|----------------------------------|
		| command |   STDIN   |   STDOUT   |
		|---------|-----------|------------|
		|  ls -l  |   fd_in   |  pipe[1]   |
		|  grep a |  pipe[0]  |  pipe[1]   |
		|  wc -l  |  pipe[0]  |  fd_out    |
		|----------------------------------|

		1) the result of the first command is written to the pipe.
		2) the result of the second command is read from the pipe and written
			to the second pipe.
		3) the result of the third command is read from the second pipe and
			written to the file.
*/

void	ft_open_pipes(t_minishell *ms)
{
	int	i;

	i = 0;
	if (ms->n_pipes == 0)
		return ;
	ms->pid = (pid_t *)ft_calloc(sizeof(pid_t), ms->n_pipes + 1);
	if (!ms->pid)
		ft_perror(ms, E_MALLOC, NO);
	if (ms->n_pipes == 0)
		return ;
	ms->pipe_fd = (int **)ft_calloc(sizeof(int *), ms->n_pipes);
	if (!ms->pipe_fd)
		ft_perror(ms, E_MALLOC, NO);
	while (i < ms->n_pipes)
	{
		ms->pipe_fd[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!ms->pipe_fd[i])
			ft_perror(ms, E_MALLOC, NO);
		if (pipe(ms->pipe_fd[i]) < 0)
			ft_perror(ms, E_PIPE, NO);
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
