/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:31 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/03 18:54:42 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit_helper(t_minishell *ms)
{
	if (ms->cmd_lst->args[1] && ft_isnum(ms->cmd_lst->args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			ms->cmd_lst->args[1]);
		g_exit_status = 2;
	}
	else if (ms->cmd_lst->args[2] && ms->cmd_lst->args[1])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
}

void	ft_exit(t_minishell *ms, t_cmd *curr)
{
	(void)curr;
	if (ft_input_has_heredoc(ms) == TRUE)
	{
		printf("exit\n");
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if (ms->cmd_lst->args[1] && ((ft_atoi(ms->cmd_lst->args[1]))
			|| (ms->cmd_lst->args[1][0] == '0' && !ms->cmd_lst->args[1][1])))
		g_exit_status = ft_atoi(ms->cmd_lst->args[1]);
	else
		g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(g_exit_status);
	printf("exit\n");
	ft_exit_helper(ms);
	if (ms->n_pipes > 0)
		ft_free_pipes(ms);
	ft_free_all(ms, YES);
	exit(g_exit_status);
}
