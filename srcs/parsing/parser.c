/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:20:19 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);
void	ft_quote_remover(t_minishell *ms);
char	*ft_remove_quotes(char *cmd, int new_len, int i);

/*
	This is where we will take the input and transform it into a command table.

	The parser contains three main parts:
		* lexycal analysis: we will take the input and transform it into tokens.
		* syntax analysis: we will check if the tokens are in the correct order.
		* cmd table creation: we will create a command table with the tokens.

	In our parser, we will first check if there any unclosed quotes, then, we
	will tokenize the input, separating the input into commands and operators.
	After that, we will check if the tokens are in the correct order. If they
	are, we will expand the tokens that have $... format. Then, we will remove
	the quotes from the tokens that have quotes. Finally, we will create a table
	of commands, where each command will have its arguments, files and types.

	ft_quote_checker: we will count the quotes (that are not inside quotes) and
	check if the number of quotes is even. If it is not, it means we have
	unclosed quotes and will not continue the parsing.

	ft_quote_remover: we will see which tokens have quotes and remove them.

	ft_remove_quotes: we will pass as an argument the token that has quotes and
	the new length of the token without the quotes. Then, we will create a new
	token without the quotes and return it.

	note: we have to be very careful with the quotes, because they can be inside
	one another. For example, if we have the following input:
		echo "hello 'world'"
	we will have to remove the quotes from the token "hello 'world'" and not
	from the token "world", so the end result would be:
		echo hello 'world'
*/

int	ft_parser(t_minishell *ms, char *input)
{
	if (ft_quote_checker(input) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_tokenizer(ms, input);
	if (ft_syntax_checker(ms, ms->token_lst) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_expander(ms, ms->token_lst);
	ft_quote_remover(ms);
	if (ft_command_table_creator(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	return (EXIT_SUCCESS);
}

int	ft_quote_checker(char *input)
{
	int		n_quotes;

	n_quotes = ft_count_quotes(input);
	if (n_quotes % 2 != 0)
	{
		g_exit_status = 2;
		return (printf("%s\n", E_QUOTES) && ERROR_FOUND);
	}
	return (EXIT_SUCCESS);
}

void	ft_quote_remover(t_minishell *ms)
{
	int		i;
	int		new_len;
	char	*old_cmd;
	t_token	*curr;

	i = 0;
	new_len = 0;
	old_cmd = NULL;
	curr = ms->token_lst;
	while (curr)
	{
		if (curr->type == T_OTHER && ft_count_quotes(curr->content) > 0)
		{
			old_cmd = curr->content;
			new_len = ft_strlen(curr->content) - ft_count_quotes(curr->content);
			curr->content = ft_remove_quotes(curr->content, new_len, i);
			free(old_cmd);
		}
		curr = curr->next;
	}
}

char	*ft_remove_quotes(char *cmd, int new_len, int i)
{
	int		in_squote;
	int		in_dquote;
	char	*new_cmd;

	in_squote = 0;
	in_dquote = 0;
	new_cmd = ft_calloc(new_len + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (i < new_len)
	{
		if ((*cmd == '\'' && !in_dquote) || (*cmd == '\"' && !in_squote))
		{
			if (*cmd == '\'' && in_dquote == 0)
				in_squote = 1 - in_squote;
			else if (*cmd == '\"' && in_squote == 0)
				in_dquote = 1 - in_dquote;
			cmd++;
		}
		else
			new_cmd[i++] = *cmd++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}
