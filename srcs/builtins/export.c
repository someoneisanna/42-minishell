/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 17:22:52 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_export_red(t_minishell *ms)
{
	t_env	*envi;

	envi = ms->env_lst;
	while (envi)
	{
		printf("declare -x ");
		printf("%s=%s\n", envi->key, envi->value);
		envi = envi->next;
	}
	if(ms->n_pipes > 0)
		ft_free_pipes(ms);
	if(ms->cmd_lst->args[1] != NULL)
		ft_free_all(ms, NO);
	g_exit_status = 0;
}

void	ft_export(t_minishell *ms)
{
	char	*key;
	char	*value;
	char	*equal_ptr;
	int 	i;
	int 	j;

	i = -1;
	// while(ms->cmd_lst->args[++i])
	// 	printf("arg[%i] %s\n", i, ms->cmd_lst->args[i]);
	if(is_there_redirections(ms) == TRUE || ms->cmd_lst->args[1] == NULL)
	{
		ft_export_red(ms);
		return ;
	}
	if (!is_option_valid(ms))
	{
		g_exit_status = 2;
		return ; 
	}
	ft_unset(ms);
	if (g_exit_status == 1)
		return ;
	i = 0;
	j = 2;
	while(ms->cmd_lst->args[i])
	{
		while(ms->cmd_lst->args[++i])
		{
			if (!ft_test_args(ms->cmd_lst->args[i]))
				break;
			equal_ptr = ft_strchr(ms->cmd_lst->args[i], '=');
			if(!equal_ptr)
				break ;
			key = ft_substr(ms->cmd_lst->args[i], 0, equal_ptr - ms->cmd_lst->args[i]);
			value = equal_ptr + 1;
			// if (!ft_quote_checker(ms->input) && ms->cmd_lst->args[2])
			// 	while(ms->cmd_lst->args[j])
			// 		value = ft_strjoin(value, ms->cmd_lst->args[j++]);
			if (!*key)
			{
				printf("minishell: export: `%s': not a valid identifier\n", equal_ptr);
				g_exit_status = 1;
				break ;
			}
			ft_add_env_back(&ms->env_lst, ft_new_env(key, value));
			free(key);
		}
	}
	if (ms->n_pipes != 0)
		exit(0);
}
