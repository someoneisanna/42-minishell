/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 15:53:30 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	Note: we also implemented here a quote checker, which will see if the input has any unclosed quotes (as the subject requires).
*/

int	ft_parser(t_minishell *ms, char *input)
{
	if (ft_quote_checker(input) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_tokenizer(ms, input);
	if (ft_syntax_checker(ms, ms->token_lst) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_expander(ms, ms->token_lst);
	if (ft_command_table_creator(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	if (ms->file_error == YES)
		return (EXIT_FAILURE);
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
		return (printf("%s\n", E_QUOTES) && EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
