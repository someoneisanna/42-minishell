/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:58:00 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/06 16:10:04 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_args_are_valid(char *arg, int export_flag);
int		ft_strmlen(char *s, char match);
void	ft_unsetable(t_minishell *ms, char *cmd);

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
	}
	ft_free_str_array(path_array);
}
