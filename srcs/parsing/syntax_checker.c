/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:03:52 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 15:18:51 by jmarinho         ###   ########.fr       */
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
