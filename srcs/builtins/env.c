/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 15:51:03 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_exit_status;

void	ft_env(t_minishell *ms)
{
	t_env	*envi;

	envi = ms->env_lst;
	if (!is_option_valid(ms))
		g_exit_status = 125;
	else if (ms->cmd_lst->args[1])
	{
		printf("minishell: env: %s: No such file or directory\n", ms->cmd_lst->args[1]);
		g_exit_status = 127;
	}
	else
	{
		while (envi)
		{
			printf("%s=%s\n", envi->key, envi->value);
			envi = envi->next;
		}
		g_exit_status = 0;
		if(ms->n_pipes > 0)
			ft_free_pipes(ms);
	}
	ft_free_all(ms, YES);
	exit(g_exit_status);
}
