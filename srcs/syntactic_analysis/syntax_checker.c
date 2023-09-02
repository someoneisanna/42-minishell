/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/02 16:31:44 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Here we check if the user is passing commands in the right order.
	It checks:
		1) If the first token is not a pipe or a redirection.
		2) If pipes and redirections are not next to each other.
		3) If the last token is not a pipe or a redirection.
*/

int	ft_syntax_checker(t_token *token)
{
	t_token	*curr;
	t_token *next;
	t_token *prev;

	curr = token;
	if (!ft_is_cmd_or_file(curr->type))
		return (ft_perror(E_SYNTAX));
	while (curr && curr->next)
	{
		prev = curr->prev;
		next = curr->next;
		if (!ft_is_cmd_or_file(curr->type) && !ft_is_cmd_or_file(next->type))
			return (ft_perror(E_SYNTAX));
		if (!ft_is_cmd_or_file(curr->type) && !ft_is_cmd_or_file(prev->type))
			return (ft_perror(E_SYNTAX));
		curr = curr->next;
	}
	if (!ft_is_cmd_or_file(curr->type))
		return (ft_perror(E_SYNTAX));
	return (EXIT_SUCCESS);
}
