/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:32:41 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 18:12:27 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_find_n(char **args)
{
	int		newline_flag;

	newline_flag = 1;
	if (args[1][0] == '-' && args[1][1] == 'n')
		newline_flag = 0;
	return (newline_flag);
}

void	ft_echo(t_minishell *ms)
{
	int	i;
	int	newline_flag;

	i = 0;
	if (ms->cmd_lst->args[1] == NULL)
	{
		printf("\n");
		g_exit_status = 0;
		ft_free_all(ms, YES);
		exit(g_exit_status);
	}
	if (ms->cmd_lst->args[1][0] == '~' && ms->cmd_lst->args[1][1] == '/')
	{
		printf("%s", ft_get_env_value(&ms->env_lst, "HOME"));
		if(ms->cmd_lst->args[1][1])
		{
			i++;
			while(ms->cmd_lst->args[1][i])
				printf("%c", ms->cmd_lst->args[1][i++]);
		}
		printf("\n");
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if (ft_quote_checker(ms->input) == ERROR_FOUND)
	{
		printf("%s\n", ms->cmd_lst->args[1]);
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if((ms->cmd_lst->args[1][1] == 'e' || ms->cmd_lst->args[1][1] == 'E') && ms->cmd_lst->args[1][2] == '\0')
	{
		if (!is_option_valid(ms))
		{
			g_exit_status = 1;
			ft_free_all(ms, YES);
			exit(g_exit_status);
		}
		exit(g_exit_status);
	}
	newline_flag = ft_find_n(ms->cmd_lst->args);
	if (newline_flag)
		i = 1;
	else
	{
		i = 2;
		while(ms->cmd_lst->args[i] && (ms->cmd_lst->args[i][0] == '-' && ms->cmd_lst->args[i][1] == 'n'))
			i++;
	}
	if(ms->cmd_lst->args[1][0] == '$')
		i++;
	while (ms->cmd_lst->args[i])
	{
		if (ms->cmd_lst->args[i][0] == '\0')
			i++;
		if (!ms->cmd_lst->args[i + 1] && ms->cmd_lst->args[i])
			printf("%s", ms->cmd_lst->args[i]);
		else if (ms->cmd_lst->args[i])
			printf("%s ", ms->cmd_lst->args[i]);
		i++;
	}
	if (newline_flag == 1)
		printf("\n");
	g_exit_status = 0;
	ft_free_all(ms, YES);
	exit(g_exit_status);
}
