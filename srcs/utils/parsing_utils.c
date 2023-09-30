/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:56:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/30 10:10:48 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_is_space(char c);
int		ft_len_until_match(char *input, char *match);
int		ft_is_cmd_or_file(t_type type);
int		ft_count_heredocs(t_token *first);

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (YES);
	return (NO);
}

int	ft_len_until_match(char *input, char *match)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(match, input[i]) == NULL)
		i++;
	return (i);
}

int	ft_is_cmd_or_file(t_type type)
{
	if (type == T_OTHER || type == T_QUOTE || type == T_DQUOTE)
		return (YES);
	return (NO);
}

int	ft_count_heredocs(t_token *first)
{
	int		n_heredocs;
	t_token	*curr;

	n_heredocs = 0;
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_DELIMITER)
			n_heredocs++;
		curr = curr->next;
	}
	return (n_heredocs);
}
