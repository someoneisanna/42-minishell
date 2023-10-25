/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:31:45 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/18 15:05:47 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_minishell *ms)
{
	char	currentdir[200];
	char	*old_dir;
	int 	arg_flag;

	arg_flag = 0;
	if(is_there_redirections(ms) == TRUE)
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if (!is_option_valid(ms))
	{
		g_exit_status = 1;
		return ; 
	}
	old_dir = ft_find_env(ms->env_lst, "OLDPWD");
	getcwd(currentdir, sizeof(currentdir));
	if (ms->cmd_lst->args[1] && ms->cmd_lst->args[1][0] != '~')
	{
		if (ft_strlen(ms->cmd_lst->args[1]) == 1 && ms->cmd_lst->args[1][0] == '-')
		{
			printf("%s\n", old_dir);
			arg_flag = chdir(old_dir);
		}
		else
			arg_flag = chdir(ms->cmd_lst->args[1]);
	}
	else if (!ms->cmd_lst->args[1] || ms->cmd_lst->args[1][0] == '~')
		arg_flag = chdir(ft_find_env(ms->env_lst, "HOME"));
	if (ms->cmd_lst->args[1] && ms->cmd_lst->args[2])
		printf("minishell: cd: too many arguments\n");
	else if (arg_flag == -1)
		printf("minishell: cd: %s: No such file or directory\n", ms->cmd_lst->args[1]);
	old_dir = currentdir;
	ft_update_env(&ms->env_lst, "OLDPWD", ft_strdup(currentdir));
	getcwd(currentdir, sizeof(currentdir));
	ft_update_env(&ms->env_lst, "PWD", ft_strdup(currentdir));
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(g_exit_status);
}
