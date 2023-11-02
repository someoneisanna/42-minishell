/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:14 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/02 17:02:56 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_builtin_error(t_minishell *ms, t_cmd *curr, char *err, int ex_code);
char	*ft_find_env(t_env *env_lst, char *find);
void	ft_update_env(t_env **env_lst, char *key, char *update);
char	ft_strchr2(const char *str, char c);
void	ft_lstadd_back2(t_env *env_lst, t_env *new_envi);

void	ft_builtin_error(t_minishell *ms, t_cmd *curr, char *err, int ex_code)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err)
		printf("minishell: %s: %s\n", curr->cmd, err);
	g_exit_status = ex_code;
	if (ms->n_pipes > 0)
		exit(g_exit_status);
}

char	*ft_find_env(t_env *env_lst, char *find)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (!ft_strcmp(current->key, find))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_update_env(t_env **env_lst, char *key, char *update)
{
	t_env	*current;

	current = *env_lst;
	while (current->next)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(current->key)))
		{
			free(current->value);
			current->value = update;
			break ;
		}
		current = current->next;
	}
}

char	ft_strchr2(const char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (str[i]);
	}
	if (str[i] == c)
		return (str[i]);
	return (0);
}

void	ft_lstadd_back2(t_env *env_lst, t_env *new_envi)
{
	t_env	*ptr;

	ptr = env_lst;
	if (env_lst)
	{
		if (!(env_lst))
		{
			env_lst = new_envi;
		}
		else
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new_envi;
		}
	}
}
