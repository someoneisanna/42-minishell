/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 11:17:00 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);
void	ft_quote_remover(t_minishell *ms);
char	*ft_remove_quotes(char *cmd, int new_len, int i);

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

int		ft_quote_checker(char *input)
{
	int		n_quotes;

	n_quotes = ft_count_quotes(input);
	if (n_quotes % 2 != 0)
		return (printf("%s\n", E_QUOTES) && ERROR_FOUND);
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
		if ((*cmd == '\'' && in_dquote == 0) || (*cmd == '\"' && in_squote == 0))
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
