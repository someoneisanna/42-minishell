/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:56:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/15 17:53:39 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_str_array(char **str_array);
char	**ft_get_paths(t_env *env_lst);
int		ft_cmd_has_redir(t_cmd *cmd);

void	ft_free_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (!str_array)
		return ;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

char	**ft_get_paths(t_env *env_lst)
{
	t_env	*env;
	char	**path_array;

	env = env_lst;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			path_array = ft_split(env->value, ':');
			return (path_array);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_cmd_has_redir(t_cmd *cmd)
{
	if (cmd->file_in)
		return (YES);
	if (cmd->file_tr)
		return (YES);
	if (cmd->heredoc)
		return (YES);
	if (cmd->file_ap)
		return (YES);
	return (NO);
}
