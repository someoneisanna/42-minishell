/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:36:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 16:52:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp2(t_minishell *ms, t_env *envi)
{
	int i;
	
	i = 0;

	while (ms->cmd_lst->args[1][i] && envi->key[i] && (ms->cmd_lst->args[1][i] == envi->key[i]))
		i++;
	if(i > 0 && ms->cmd_lst->args[1][i] == '=')
	 	i--;
	return((unsigned char)ms->cmd_lst->args[1][i] - (unsigned char)envi->key[i]);
} 

int	ft_unset(t_minishell *ms)
{
	int i;
	t_env	*envi;
	t_env	*prev;

	if(ms->cmd_lst->args[1] == NULL)
	{
		g_exit_status = 0;
		return (g_exit_status);
	}
	if(is_there_redirections(ms) == TRUE)
		exit(0);
	if (!is_option_valid(ms))
	{
		g_exit_status = 2;
		return (g_exit_status); 
	}
	i = 0;
	while(ms->cmd_lst->args[1][i] != '=' && ms->cmd_lst->args[1][i])
	{
		if (!ft_test_args(ms->cmd_lst->args[i]))
			break ;
		i++;
	}
	// 	if((!ft_isalpha(ms->cmd_lst->args[1][0]) || !ft_isalnum(ms->cmd_lst->args[1][i]))
	// 		&& !ft_strchr(ms->cmd_lst->args[1], '_'))
	// 	{
	// 		printf("minishell: %s: %s: not a valid identifier\n", ms->cmd_lst->args[0], ms->cmd_lst->args[1]);
	// 		g_exit_status = 1;
	// 		return (g_exit_status);
	// 	}
	// 	i++;
	// }
	i = 0;
	envi = ms->env_lst;
	prev = NULL;
	while(envi)
	{
		if (ft_strcmp2(ms, envi) == 0)
		{	
			 if (prev == NULL)
                ms->env_lst = envi->next;
            else
                prev->next = envi->next;
			free(envi->key);
			free(envi->value);
			free(envi);
			break;
		}
		prev = envi;
        envi = envi->next;
	}
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(0);
	return (g_exit_status);
}
