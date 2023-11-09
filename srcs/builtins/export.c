/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/09 12:33:13 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_minishell *ms, t_cmd *curr);
int		ft_export_variable(t_minishell *ms, t_cmd *curr, int i);
void	ft_export_list(t_minishell *ms, t_cmd *curr);
void	ft_sort_env(t_env *env);
void	ft_swap_env(t_env *curr, t_env *next);

void	ft_export(t_minishell *ms, t_cmd *curr)
{
	int	i;

	i = 0;
	if (curr->args[1] == NULL)
		return (ft_export_list(ms, curr));
	if (!ft_cmd_has_valid_option(curr->args))
		return (ft_builtin_error(ms, curr, NULL, 2));
	if (g_exit_status == 1)
		return ;
	while (curr->args[i])
	{
		while (curr->args[++i])
		{
			if (ft_strlen(curr->args[i]) == 0)
			{
				ft_builtin_error(ms, curr, "", 1);
				break ;
			}
			ft_export_unset(ms, curr->args[i]);
			if (ft_export_variable(ms, curr, i) == ERROR_FOUND)
				break ;
		}
	}
	if (ms->n_pipes > 0)
		ft_free_all(ms, YES);
}

int	ft_export_variable(t_minishell *ms, t_cmd *cur, int i)
{
	char	*key;
	char	*value;
	char	*equal_ptr;

	if (!ft_args_are_valid(cur->args[i], YES) || ms->n_pipes > 0)
		return (ERROR_FOUND);
	if (!ft_strchr(cur->args[i], '=') && ft_find_env(ms->env_lst, cur->args[i]))
		return (ERROR_FOUND);
	equal_ptr = ft_strchr(cur->args[i], '=');
	if (!equal_ptr)
	{
		ft_add_env_back(&ms->env_lst, ft_new_env(cur->args[i], NULL));
		return (EXIT_SUCCESS);
	}
	key = ft_substr(cur->args[i], 0, equal_ptr - cur->args[i]);
	if (!*key)
	{
		free(key);
		ft_builtin_error(ms, cur, equal_ptr, 1);
		return (ERROR_FOUND);
	}
	value = equal_ptr + 1;
	ft_add_env_back(&ms->env_lst, ft_new_env(key, value));
	free(key);
	return (EXIT_SUCCESS);
}

void	ft_export_list(t_minishell *ms, t_cmd *curr)
{
	t_env	*sorted_env;

	ft_sort_env(ms->env_lst);
	sorted_env = ms->env_lst;
	while (sorted_env)
	{
		ft_putstr_fd("declare -x ", curr->fd_out);
		ft_putstr_fd(sorted_env->key, curr->fd_out);
		if (sorted_env->value)
		{
			ft_putstr_fd("=\"", curr->fd_out);
			ft_putstr_fd(sorted_env->value, curr->fd_out);
			ft_putstr_fd("\"", curr->fd_out);
		}
		ft_putstr_fd("\n", curr->fd_out);
		sorted_env = sorted_env->next;
	}
	g_exit_status = 0;
	if (ms->n_pipes > 0)
		ft_free_all(ms, YES);
}

void	ft_sort_env(t_env *env)
{
	t_env	*curr;
	int		swapped;

	curr = env;
	swapped = 1;
	while (swapped)
	{
		curr = env;
		swapped = 0;
		while (curr->next)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
			{
				ft_swap_env(curr, curr->next);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
}

void	ft_swap_env(t_env *curr, t_env *next)
{
	char	*key_tmp;
	char	*val_tmp;

	key_tmp = curr->key;
	val_tmp = curr->value;
	curr->key = next->key;
	curr->value = next->value;
	next->key = key_tmp;
	next->value = val_tmp;
}
