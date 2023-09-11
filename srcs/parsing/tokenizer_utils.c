/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:14:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/04 15:29:52 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token *ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);
void	ft_free_token_lst(t_token **token_lst);

/*
	Here are the functions that helped us to build the doubly linked list.
	The logic is very similar to the one used in normal linked lists, but we have to add the *prev pointer (see ft_add_token_back()).
*/

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

void	ft_free_token_lst(t_token **token_lst)
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