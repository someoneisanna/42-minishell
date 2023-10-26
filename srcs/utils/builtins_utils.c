/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:14 by jmarinho          #+#    #+#             */
/*   Updated: 2023/10/26 17:20:09 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_find_env(t_env *env_lst, char *find)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(current->key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}


void	ft_update_env(t_env **env_lst, char *key, char *update)
{
	t_env	*current;

	current = *env_lst;
	while (current)
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

char ft_strchr2(const char *str, char c)
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

bool ft_not_forkable(t_minishell *ms)
{
	t_token *token;

	token = ms->token_lst;
	while (token)
	{
		if (ft_strncmp(token->content, "<<", 3) == 0)
			return (FALSE);
		token = token->next;
	}
	if (ft_strncmp(ms->cmd_lst->cmd, "export", 7) == 0)
	{
		ft_export(ms);
		return (TRUE);
	}
	else if (ft_strncmp(ms->cmd_lst->cmd, "unset", 6) == 0)
	{
		ft_unset(ms);
		return (TRUE);
	}
	else if (ft_strncmp(ms->cmd_lst->cmd, "cd", 3) == 0)
	{
		ft_cd(ms);
		return (TRUE);
	}
	else if (ft_strncmp(ms->cmd_lst->cmd, "exit", 5) == 0)
	{
		ft_exit(ms);
		return (TRUE);
	}
	return(FALSE);
}

bool is_there_redirections(t_minishell *ms)
{
	t_token *token;

	token = ms->token_lst;
	while (token)
	{
		if (ft_strncmp(token->content, "<<", 3) == 0)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

bool is_option_valid(t_minishell *ms)
{
	if(ms->cmd_lst->args[1] && (ft_strncmp(ms->cmd_lst->args[0], "cd", 3) == 0 && ms->cmd_lst->args[1][0] == '-'))
		return (TRUE);
	if (ms->cmd_lst->args[1])
	{
		if (ms->cmd_lst->args[1][0] == '-')
		{
			printf("minishell: %s: -%c: invalid option\n", ms->cmd_lst->args[0], ms->cmd_lst->args[1][1]);
			return(FALSE);
		}
	}
	return(TRUE);
}

void ft_unsetable(t_minishell *ms, char *cmd)
{
	char **path_array;

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
	if(!path_array)
	{
		printf("minishel: %s: No such file or directory\n", cmd);
		g_exit_status = 127;
	}
	ft_free_str_array(path_array);
}

bool ft_test_args(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if(!ft_isalpha(arg[0]) || (!ft_isalnum(arg[i]) && arg[i] != '_'))
		{
			printf("minishell: %s: not a valid identifier\n", arg);
			g_exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
 