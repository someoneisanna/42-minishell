/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:51:46 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/05 10:15:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);

/*
	This is where we will check if the command has a variable that needs to be expanded.
	We will only expand variables that are followed by $.
	Reminders:
		When a command has single quotes, we don't expand anything (we will only expand when the token is T_DQUOTE or T_OTHER)
		$? is a special variable that expands to the exit status of the last command.
*/

void	ft_expander(t_minishell *ms, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type == T_DQUOTE || curr->type == T_OTHER)
			ft_expand_command(ms, curr);
		curr = curr->next;
	}
}

void	ft_expand_command(t_minishell *ms, t_token *token)
{
	char	*tmp;
	char	*key;
	char	*value;

	while (ft_strchr(token->content, '$') != NULL)
	{
		key = ft_get_key(token->content);
		if (ft_strncmp(key, "$?", 2) == 0)
			value = ft_itoa(42); //create a exit status variable
		else
			value = ft_get_env_value(&ms->env, key);
		tmp = token->content;
		token->content = ft_replace_content(token->content, key, value);
		free(tmp);
		free(key);
		free(value);
	}
}

char	*ft_get_key(char *cmd)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd));
	if (tmp == NULL)
		return (NULL);
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	while (tmp[len + 1] == '_' || ft_isalnum(tmp[len + 1]) == YES)
		len++;
	return (ft_substr(tmp, 0, len + 1));
}

char	*ft_get_env_value(t_env **env_lst, char *key)
{
	t_env	*current;

	current = *env_lst;
	if (key[0] == '$')
		key++;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_replace_content(char *cmd, char *key, char *value)
{
	char	*key_ptr;
	char	*new_cmd;
	int		new_len;

	if (!cmd || !key || !value)
		return (NULL);
	new_len = ft_strlen(cmd) - ft_strlen(key) + ft_strlen(value);
	new_cmd = ft_calloc(new_len + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	key_ptr = ft_strnstr(cmd, key, ft_strlen(cmd));
	if (!key_ptr)
		return (NULL);
	ft_strlcpy(new_cmd, cmd, ft_strlen(cmd) - ft_strlen(key_ptr) + 1);
	ft_strlcat(new_cmd, value, new_len + 1);
	ft_strlcat(new_cmd, key_ptr + ft_strlen(key), new_len + 1);
	return (new_cmd);
}
