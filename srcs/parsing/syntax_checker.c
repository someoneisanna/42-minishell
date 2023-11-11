/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/11 11:00:36 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (curr->type != T_OTHER && next->type != T_OTHER)
		{
			if (curr->type == T_PIPE && next->type != T_PIPE)
				;
			else
				return (ft_perror(ms, E_SYNTAX, NO, NULL));
		}
		curr = curr->next;
	}
	if (curr->type != T_OTHER)
		return (ft_perror(ms, E_SYNTAX, NO, NULL));
	return (EXIT_SUCCESS);
}
