/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:06:37 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/02 18:19:46 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

/*
	This is the first step of the parser, where the input is split into tokens.
	Each token will have assigned it's content and type.
	The type is used to build the command table and execute the commands.
	We will use a doubly linked list to store the tokens, so we can easily work with the commands (there is a *prev and *next pointer in the struct).
*/

void	ft_tokenizer(t_minishell *ms, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]) == YES)
			i++;
		else if (input[i] == '|')
			i += ft_add_token(&ms->token, "|", T_PIPE);
		else if (input[i] == '<' && input[i + 1] != '<')
			i += ft_add_token(&ms->token, "<", T_REDIR_IN);
		else if (input[i] == '>' && input[i + 1] != '>')
			i += ft_add_token(&ms->token, ">", T_REDIR_OUT);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += ft_add_token(&ms->token, "<<", T_REDIR2_IN);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += ft_add_token(&ms->token, ">>", T_REDIR2_OUT);
		else if (input[i] == '\'')
			i += ft_add_command_token(&ms->token, input + i, T_QUOTE);
		else if (input[i] == '\"')
			i += ft_add_command_token(&ms->token, input + i, T_DQUOTE);
		else
			i += ft_add_command_token(&ms->token, input + i, T_OTHER);
	}
}

int	ft_add_token(t_token **token_lst, char *input, t_type type)
{
	t_token	*new_token;

	new_token = ft_new_token(input, type);
	if (!new_token || !input)
		return (0);
	ft_add_token_back(token_lst, new_token);
	return (ft_strlen(input));
}

int	ft_add_command_token(t_token **token_lst, char *input, t_type type)
{
	char	*match;
	char	*command;
	int		found_match;

	if (type == T_QUOTE || type == T_DQUOTE)
	{
		if (type == T_QUOTE)
			match = "\'";
		else if (type == T_DQUOTE)
			match = "\"";
		found_match = ft_len_until_match(input + 1, match) + 2;
		command = ft_substr(input, 1, found_match - 2);
	}
	else
	{
		match = "<>\'\"| ";
		found_match = ft_len_until_match(input, match);
		command = ft_substr(input, 0, found_match);
	}
	ft_add_token(token_lst, command, type);
	free(command);
	return (found_match);
}
