/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:56:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 16:49:17 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_is_space(char c);
int		ft_is_symbol(char c);
int		ft_count_quotes(char *s);
int		ft_in_squote(char *cmd, char *stop);
int		ft_count_redir(t_token *first, t_type type, t_type type2);

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (YES);
	return (NO);
}

int	ft_is_symbol(char c)
{
	if (c == '\"' || c == '\'' || c == '@' || c == '*' || c == '!')
		return (1);
	else if (c == '.' || c == ',' || c == '+' || c == '%' || c == '='
		|| c == '~' || c == '^' || c == '/')
		return (2);
	else
		return (0);
}

int	ft_count_quotes(char *s)
{
	int		i;
	int		n_quotes;
	int		in_squote;
	int		in_dquote;

	i = 0;
	n_quotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && in_dquote == 0)
		{
			in_squote = 1 - in_squote;
			n_quotes++;
		}
		else if (s[i] == '"' && in_squote == 0)
		{
			in_dquote = 1 - in_dquote;
			n_quotes++;
		}
		i++;
	}
	return (n_quotes);
}

int	ft_in_squote(char *cmd, char *stop)
{
	int		i;
	int		n_squotes;
	int		in_squote;
	int		in_dquote;

	i = 0;
	n_squotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (cmd[i] && &cmd[i] != stop)
	{
		if (cmd[i] == '\'' && in_dquote == 0)
		{
			in_squote = 1 - in_squote;
			n_squotes++;
		}
		else if (cmd[i] == '"' && in_squote == 0)
			in_dquote = 1 - in_dquote;
		i++;
	}
	if (n_squotes % 2 == 0)
		return (NO);
	return (YES);
}

int	ft_count_redir(t_token *first, t_type type1, t_type type2)
{
	int		n_redirs;
	t_token	*curr;

	n_redirs = 0;
	curr = first;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == type1 || curr->type == type2)
			n_redirs++;
		curr = curr->next;
	}
	return (n_redirs);
}
