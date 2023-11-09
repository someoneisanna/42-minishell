/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/09 12:51:06 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Here we will check if the tokens are in the correct order.

	We will return error if:
		* the first token is an.
		* there are two operators next to each other.
		* the last token is an operator.

	Operators: | < > << >>
*/

int	ft_syntax_checker(t_minishell *ms, t_token *token)
{
	t_token	*curr;
	t_token	*next;

	curr = token;
	if (curr->type == T_PIPE)
		return (ft_perror(ms, E_SYNTAX, NO, NULL));
	while (curr && curr->next)
	{
		next = curr->next;
		if (curr->type == T_PIPE && next->type == T_PIPE)
			return (ft_perror(ms, E_SYNTAX, NO, NULL));
		if (ft_is_redir(curr->type) == YES && ft_is_redir(next->type) == YES)
			return (ft_perror(ms, E_SYNTAX, NO, NULL));
		if (ft_is_redir(curr->type) == YES && next->type == T_PIPE)
			return (ft_perror(ms, E_SYNTAX, NO, NULL));
		curr = curr->next;
	}
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO, NULL));
	return (EXIT_SUCCESS);
}

int	ft_is_redir(t_type type)
{
	if (type == T_REDIR_IN
		|| type == T_REDIR_OUT || type == T_REDIR2_OUT
		|| type == T_REDIR2_IN || type == T_HEREDOC)
		return (YES);
	return (NO);
}
