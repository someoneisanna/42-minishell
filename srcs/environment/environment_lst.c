/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:25:15 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 12:05:35 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_init_env_lst(t_env **env, char **envp);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env_back(t_env **env_lst, t_env *new_env);
char	**ft_get_paths(t_env *env_lst);

/*
	In this file, we will create a linked list of environment variables.
	The values in this list are basically the same as the ones you get when you run the command "env" in the terminal.
	The list is organized in a way that:
		key: HOME
		value: /home/anna
	There are a few uses for this list in minishell:
		1) Expansions: When we expand a environment variable, we will need to get the value from this list.
*/

void	ft_init_env_lst(t_env **env, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_ptr;

	i = 0;
	ft_bzero(env, sizeof(t_env));
	while (envp[i] != NULL)
	{
		equal_ptr = ft_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, equal_ptr - envp[i]);
		value = equal_ptr + 1;
		ft_add_env_back(env, ft_new_env(key, value));
		free(key);
		i++;
	}
}

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_env_back(t_env **env_lst, t_env *new_env)
{
	t_env	*current;

	if (!*env_lst)
	{
		*env_lst = new_env;
		return ;
	}
	current = *env_lst;
	while (current && current->next)
		current = current->next;
	current->next = new_env;
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
