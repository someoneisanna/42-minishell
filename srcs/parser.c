/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/07 18:16:51 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);

/*
	When building a shell, the first step is parsing the input.
	Our parser has four main steps:
	1) Lexical analysis: The input is split into tokens (tokenizer).
	2) Syntax analysis: The tokens are checked for syntax errors (syntax checker)
	3) Expansion: the tokens are scanned for special characters and expanded
	   (expander).
	4) Command Table Construction: The tokens are converted into a command table (command_table_creator).
*/

int	ft_parser(t_minishell *ms, char *input)
{
	if (ft_quote_checker(input) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_tokenizer(ms, input);
	if (ft_syntax_checker(ms->token) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_expander(ms, ms->token);
	ft_command_table_creator(ms);
	return (EXIT_SUCCESS);
}

int		ft_quote_checker(char *input)
{
	int i;
	int closed_quote;

	i = 0;
	closed_quote = YES;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (closed_quote == YES)
				closed_quote = NO;
			else if (closed_quote == NO)
				closed_quote = YES;
		}
		i++;
	}
	if (closed_quote == NO)
		return (ft_perror(E_QUOTES));
	return (EXIT_SUCCESS);
}
