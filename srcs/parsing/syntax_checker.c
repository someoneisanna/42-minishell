/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:31:38 by ataboada         ###   ########.fr       */
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
	t_token	*prev;

	curr = token;
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO, NULL));
	while (curr && curr->next)
	{
		prev = curr->prev;
		next = curr->next;
		if (curr->type != T_OTHER && next->type != T_OTHER)
			return (ft_perror(ms, E_SYNTAX, NO, NULL));
		if (curr->type != T_OTHER && prev->type != T_OTHER)
			return (ft_perror(ms, E_SYNTAX, NO, NULL));
		curr = curr->next;
	}
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO, NULL));
	return (EXIT_SUCCESS);
}
