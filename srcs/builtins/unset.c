/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:36:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/03 18:57:00 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_unset(t_minishell *ms);
void	ft_unset_helper(t_minishell *ms, t_env *curr, t_env *prev);
bool	ft_unset_cicle(t_minishell *ms);
int		ft_strcmp2(char *arg, char *key);

// int	ft_strcmp2(char *arg, char *key)
// {
// 	int i;
	
// 	i = 0;
// 	while (arg[i] && key[i] && (arg[i] == key[i]))
// 		i++;
// 	if(i > 0 && arg[i] == '=')
// 	 	i--;
// 	return((unsigned char)arg[i] - (unsigned char)key[i]);
// } 

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (!s1 && !s2)
// 		return (0);
// 	if (!s1 || !s2)
// 		return (1);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			break ;
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }

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
	if (!ft_cmd_has_valid_option(ms->cmd_lst->args))
	{
		g_exit_status = 2;
		return (g_exit_status); 
	}
	i = 0;
	while(ms->cmd_lst->args[i] && ms->cmd_lst->args[1][i] != '=' && ms->cmd_lst->args[1][i])
	{
		if (!ft_args_are_valid(ms->cmd_lst->args[i]))
			break ;
		i++;
	}
	i = 1;
	envi = ms->env_lst;
	prev = NULL;
	while(ms->cmd_lst->args[i])
	{
		envi = ms->env_lst;
		while(envi)
		{
			if (ft_strncmp(ms->cmd_lst->args[i], envi->key, ft_len_until_match(ms->cmd_lst->args[i], "=")) == 0)
			{	
				if (ms->cmd_lst->args[i][0] == '=')
					break ;
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
		i++;
	}
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(0);
	return (g_exit_status);
}
