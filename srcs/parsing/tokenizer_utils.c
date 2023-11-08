/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:14:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:29:16 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);

/*
	These are standart function to add nodes to a list.

	ft_new_token allocates memory for a new token and everything inside it.

	ft_add_token_back adds a new token to the end of the token list.
*/

t_token	*ft_new_token(char *input, t_type type)
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
