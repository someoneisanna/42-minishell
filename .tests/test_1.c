/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:52:53 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/02 10:21:55 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"

// ---------------------------------- STRUCTS ----------------------------------

typedef enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR2_IN,
	T_REDIR2_OUT,
	T_QUOTE,
	T_DQUOTE,
	T_OTHER,
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	char	*input;
	t_token	*token;
}	t_minishell;

// -------------------------------- PROTOTYPES ---------------------------------


int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);
int		ft_size_until_match(char *input, char *match);

t_token	*ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);

void	ft_print_token_lst(t_token *token_lst);
void	ft_clear_token_lst(t_token **token_lst);

// ---------------------------------- MAIN -------------------------------------

int main(void)
{
	t_minishell *ms = ft_calloc(1, sizeof(t_minishell));

	char *input = "before \' d u r i n g \' after \" inside \"";

	int i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
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
	printf("PRINT_TOKENS\n");
	ft_print_token_lst(ms->token);
	ft_clear_token_lst(&ms->token);
	free(ms);
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
		found_match = ft_size_until_match(input + 1, match) + 2;
		command = ft_substr(input, 1, found_match - 2);
	}
	else
	{
		match = "<>\'\"| ";
		found_match = ft_size_until_match(input, match);
		command = ft_substr(input, 0, found_match);
	}
	ft_add_token(token_lst, command, type);
	free(command);
	return (found_match);
}

int	ft_size_until_match(char *input, char *match)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(match, input[i]) == NULL)
	{
		i++;
	}
	return (i);
}

t_token *ft_new_token(char *input, t_type type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(input);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	ft_add_token_back(t_token **token_lst, t_token *new_token)
{
	t_token	*current;

	if (!*token_lst)
	{
		*token_lst = new_token;
		return ;
	}
	current = *token_lst;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	ft_print_token_lst(t_token *token_lst)
{
	t_token	*current;

	if (!token_lst)
		return ;
	current = token_lst;
	while (current)
	{
		printf("content:%s| ", current->content);
		printf("type: %d\n", current->type);
		current = current->next;
	}
}

void	ft_clear_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*next;

	if (!*token_lst)
		return ;
	current = *token_lst;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token_lst = NULL;
}
