/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:58:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/21 09:38:59 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_set_cmd_index(t_minishell *ms);
void	ft_pipes_creator(t_minishell *ms);
void	ft_pipes_handler(t_minishell *ms);
void	ft_close_pipes(t_minishell *ms);

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

void	ft_pipes_creator(t_minishell *ms)
{
	int	i;

	i = 0;
	ms->pid = (pid_t *)malloc(sizeof(pid_t) * ms->n_pipes + 1);
	if (!ms->pid)
		ft_perror(ms, E_MALLOC, YES);
	if (ms->n_pipes == 0)
		return ;
	ms->pipe_fd = (int **)malloc(sizeof(int *) * ms->n_pipes);
	if (!ms->pipe_fd)
		ft_perror(ms, E_MALLOC, YES);
	while (i < ms->n_pipes)
	{
		ms->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!ms->pipe_fd[i])
			ft_perror(ms, E_MALLOC, YES);
		if (pipe(ms->pipe_fd[i]) < 0)
			ft_perror(ms, E_PIPE, YES);
		i++;
	}
}

void	ft_pipes_handler(t_minishell *ms)
{
	(void)ms;
}

void	ft_close_pipes(t_minishell *ms)
{
	(void)ms;
}
