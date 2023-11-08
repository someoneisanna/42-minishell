/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:51:46 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:44:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);

/*
	Here is where we will expand the environment variables.

	We might need to expand a variable when we have a $ in the command.

	ft_expander:
		* we will not expand when:
			- the token is a heredoc delimiter.
			- the token is a single $.
			- the token is a $ followed by one of these symbols:
				'.' ',' '+' '%' '=' '~' '^' '/'
		* if the token is not one of the above, we will expand it.
		* after expanding, we will check if the token is empty (cases where we
		have a $ followed by a variable that does not exist) -> $bwkfvw. if it's
		the case, we will change the token type to T_EMPTY.

	ft_expand_command:
		* while we have $ in the token content, we will expand it.
		* however, if the $ is inside single quotes, we will not expand it.
		* after checking that it is not inside single quotes, we will get the
		key and the value of the variable.
		* what is after $ is the key, and what matches the key in the env_lst is
		the value.

	For example,
		echo $USER -> USER is the key, and it matches the key USER in the
		env_lst, so its value will be the same as the value of the key USER in
		the env_lst.

	We also deal with some specific cases in which, if we have the $ followed by
	double quotes, sngle quotes, @, *, ! or a number, we will not expand it, but
	print what is after it.

	For example:
		echo $"USER" -> USER will be printed.
		echo $'USER' -> USER will be printed.
		echo $@USER -> USER will be printed.
		echo $*USER -> USER will be printed.
		echo $!USER -> USER will be printed.
		echo $1USER -> USER will be printed.
*/

void	ft_expander(t_minishell *ms, t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->prev && !ft_strcmp(curr->prev->content, "<<"))
			return ;
		if (curr->content[0] == '$'
			&& (!curr->content[1] || curr->content[1] == ' '))
			return ;
		if (curr->content[0] == '$' && ft_is_symbol(curr->content[1]) == 2)
			return ;
		if (curr->type == T_OTHER)
			ft_expand_command(ms, curr);
		if (ft_strlen(curr->content) == 0)
			curr->type = T_EMPTY;
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
		if (ft_in_squote(token->content, ft_strchr(token->content, '$')) == YES)
			return ;
		key = ft_get_key(token->content);
		if (ft_strncmp(key, "$?", 2) == 0)
			value = ft_itoa(g_exit_status);
		else
			value = ft_get_env_value(&ms->env_lst, key);
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
	if (ft_is_symbol(tmp[1]) == 1)
		len++;
	while (ft_isalnum(tmp[len + 1]) != 0 || tmp[len + 1] == '_')
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
		if (ft_strcmp(current->key, key) == 0)
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

	if (ft_isalnum(key[1]) == 1 || ft_is_symbol(key[1]) == 1)
		return (ft_strdup(key + 2));
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
