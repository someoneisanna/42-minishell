/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:56:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/02 10:18:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_is_space(char c);
int		ft_len_until_match(char *input, char *match);
int		ft_is_cmd_or_file(t_type type);
int		ft_count_redir(t_token *first, t_type type);

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

int	ft_count_redir(t_token *first, t_type type)
{
	int		n_redirs;
	t_token	*curr;

	n_redirs = 0;
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type)
			n_redirs++;
		curr = curr->next;
	}
	return (n_redirs);
}
