/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:36:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/02 17:08:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_unset(t_minishell *ms);
void	ft_unset_helper(t_minishell *ms, t_env *curr, t_env *prev);
bool	ft_unset_cicle(t_minishell *ms);
int		ft_strcmp2(t_minishell *ms, t_env *envi);

int	ft_unset(t_minishell *ms)
{
	t_env	*curr;
	t_env	*prev;

	curr = NULL;
	prev = NULL;
	if (ms->cmd_lst->args[1] == NULL)
	{
		g_exit_status = 0;
		return (g_exit_status);
	}
	if (!ft_cmd_has_valid_option(ms->cmd_lst->args))
	{
		g_exit_status = 2;
		return (g_exit_status);
	}
	if (ft_unset_cicle(ms) == FALSE)
		return (g_exit_status);
	ft_unset_helper(ms, curr, prev);
	return (g_exit_status);
}

void	ft_unset_helper(t_minishell *ms, t_env *curr, t_env *prev)
{
	curr = ms->env_lst;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp2(ms, curr) == 0)
		{
			if (prev == NULL)
				ms->env_lst = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(0);
}

bool	ft_unset_cicle(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->cmd_lst->args[++i])
	{
		if (ft_strchr(ms->cmd_lst->args[i], '='))
		{
			if (ft_args_are_valid(ms->cmd_lst->args[i]) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_strcmp2(t_minishell *ms, t_env *envi)
{
	int	i;

	i = 0;
	while (ms->cmd_lst->args[1][i] && envi->key[i]
		&& (ms->cmd_lst->args[1][i] == envi->key[i]))
		i++;
	if (i > 0 && ms->cmd_lst->args[1][i] == '=')
		i--;
	return ((unsigned char)ms->cmd_lst->args[1][i]
		- (unsigned char)envi->key[i]);
}
