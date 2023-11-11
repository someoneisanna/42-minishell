/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:58:00 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/11 17:26:07 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_args_are_valid(char *arg, int export_flag);
int		ft_strmlen(char *s, char match);
void	ft_unsetable(t_minishell *ms, char *cmd);
void	ft_build_envp(t_minishell *ms);

bool	ft_args_are_valid(char *arg, int export_flag)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) || (ft_isalnum(arg[i]) == 0 && arg[i] != '_'))
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			if (export_flag == YES)
				printf("minishell: export: '%s': %s\n", arg, E_EXPORT);
			g_exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_strmlen(char *s, char match)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != match)
		i++;
	return (i);
}

void	ft_unsetable(t_minishell *ms, char *cmd)
{
	char	**path_array;

	if (ft_strncmp(cmd, "echo", 5) == 0)
		return ;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return ;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return ;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return ;
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return ;
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return ;
	path_array = ft_get_paths(ms->env_lst);
	if (!path_array)
	{
		printf("minishell: %s: no such file or directory\n", cmd);
		g_exit_status = 127;
		ft_free_all(ms, YES, YES);
	}
	ft_free_str_array(path_array);
}

void	ft_build_envp(t_minishell *ms)
{
	int		i;
	char	*tmp;
	t_env	*env;

	i = 0;
	env = ms->env_lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	ms->envp = ft_calloc(sizeof(char *), (i + 1));
	if (!ms->envp)
		ft_free_all(ms, YES, YES);
	i = 0;
	env = ms->env_lst;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ms->envp[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
}
