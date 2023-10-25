/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 15:23:07 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_syntax_checker(t_minishell *ms, t_token *token)
{
	t_token	*curr;
	t_token *next;
	t_token *prev;

	curr = token;
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO));
	while (curr && curr->next)
	{
		prev = curr->prev;
		next = curr->next;
		if (curr->type != T_OTHER && next->type != T_OTHER)
			return (ft_perror(ms, E_SYNTAX, NO));
		if (curr->type != T_OTHER && prev->type != T_OTHER)
			return (ft_perror(ms, E_SYNTAX, NO));
		curr = curr->next;
	}
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO));
	return (EXIT_SUCCESS);
}
