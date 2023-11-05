/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/04 15:51:06 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_minishell *ms, t_cmd *cur)
{
	t_env	*env;

	env = ms->env_lst;
	if (ft_cmd_has_valid_option(cur->args) == FALSE)
		g_exit_status = 125;
	else if (cur->args[1])
		ft_builtin_error(ms, cur, E_FILE, 127);
	else
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		g_exit_status = 0;
		if (ms->n_pipes > 0)
			ft_free_pipes(ms);
	}
	ft_free_all(ms, YES);
	exit(g_exit_status);
}
