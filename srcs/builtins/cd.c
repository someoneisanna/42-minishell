/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:31:45 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/02 18:43:39 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_minishell *ms, t_cmd *curr);
int		ft_cd_helper(t_minishell *ms, t_cmd *curr, char *old_dir, int arg_flag);

void	ft_cd(t_minishell *ms, t_cmd *curr)
{
	char	cur_dir[200];
	char	*old_dir;
	int		arg_flag;

	arg_flag = 0;
	old_dir = ft_find_env(ms->env_lst, "OLDPWD");
	getcwd(cur_dir, sizeof(cur_dir));
	if (!ft_cmd_has_valid_option(curr->args))
		return (ft_builtin_error(ms, curr, NULL, 2));
	if (curr->args[1] && curr->args[2])
		return (ft_builtin_error(ms, curr, "too many arguments", 1));
	arg_flag = ft_cd_helper(ms, curr, old_dir, arg_flag);
	if (arg_flag == -1)
		return (ft_builtin_error(ms, curr, E_FILE, 1));
	ft_update_env(&ms->env_lst, "OLDPWD", ft_strdup(cur_dir));
	getcwd(cur_dir, sizeof(cur_dir));
	ft_update_env(&ms->env_lst, "PWD", ft_strdup(cur_dir));
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(g_exit_status);
}

int	ft_cd_helper(t_minishell *ms, t_cmd *curr, char *old_dir, int arg_flag)
{
	if (curr->args[1])
	{
		if (ft_strlen(curr->args[1]) == 1 && curr->args[1][0] == '-')
		{
			printf("%s\n", old_dir);
			arg_flag = chdir(old_dir);
		}
		else if (ft_strlen(curr->args[1]) == 1 && curr->args[1][0] == '~')
			arg_flag = chdir(ft_find_env(ms->env_lst, "HOME"));
		else
			arg_flag = chdir(curr->args[1]);
	}
	else
		arg_flag = chdir(ft_find_env(ms->env_lst, "HOME"));
	return (arg_flag);
}
