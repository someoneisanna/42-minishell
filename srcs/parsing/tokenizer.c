/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:06:37 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:53:19 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

/*
	This is where we will take the input and transform it into tokens.

	ft_tokenizer:
		* we will iterate through the input and add tokens to the token list,
		separating the input into commands and operators.
		* as separators, we will use the following characters:
			'|' '<' '>' '<<' '>>' ' '
		* we will separate the input in the following way:
			cat < a.txt << a > b.txt | grep A | wc -l >> c.txt
			|-----------------------------------------------|
			| token		| type		  | content				|
			|-----------------------------------------------|
			| cat		| T_OTHER	  | cat					|
			| <			| T_REDIR_IN  | <					|
			| a.txt		| T_OTHER	  | a.txt				|
			| <<		| T_REDIR2_IN | <<				 	|
			| a			| T_OTHER	  | a			 		|
			| >			| T_REDIR_OUT | >					|
			| b.txt		| T_OTHER	  | b.txt				|
			| |			| T_PIPE	  | |					|
			| grep		| T_OTHER	  | grep				|
			| A			| T_OTHER	  | A					|
			| |			| T_PIPE	  | |					|
			| wc		| T_OTHER	  | wc					|
			| -l		| T_OTHER	  | -l					|
			| >>		| T_REDIR2_OUT| >>					|
			| c.txt		| T_OTHER	  | c.txt				|
			|-----------------------------------------------|
*/

void	ft_tokenizer(t_minishell *ms, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]) == YES)
			i++;
		else if (input[i] == '|')
			i += ft_add_token(&ms->token_lst, "|", T_PIPE);
		else if (input[i] == '<' && input[i + 1] != '<')
			i += ft_add_token(&ms->token_lst, "<", T_REDIR_IN);
		else if (input[i] == '>' && input[i + 1] != '>')
			i += ft_add_token(&ms->token_lst, ">", T_REDIR_OUT);
		else if (input[i] == '<' && input[i + 1] == '<')
			i += ft_add_token(&ms->token_lst, "<<", T_REDIR2_IN);
		else if (input[i] == '>' && input[i + 1] == '>')
			i += ft_add_token(&ms->token_lst, ">>", T_REDIR2_OUT);
		else
			i += ft_add_command_token(&ms->token_lst, input + i, T_OTHER);
	}
}

int	ft_add_token(t_token **token_lst, char *input, t_type type)
{
	t_token	*new_token;

	new_token = ft_new_token(input, type);
	if (!new_token || !input)
		return (0);
	ft_add_token_back(token_lst, new_token);
	return (ft_strlen(input));
}

int	ft_add_command_token(t_token **token_lst, char *input, t_type type)
{
	int		i;
	char	*cmd;
	int		in_squote;
	int		in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && in_dquote == 0)
			in_squote = 1 - in_squote;
		else if (input[i] == '"' && in_squote == 0)
			in_dquote = 1 - in_dquote;
		else if ((input[i] == ' ' || input[i] == '>' || input[i] == '<'
			|| input[i] == '|') && in_squote == 0 && in_dquote == 0)
			break ;
		i++;
	}
	cmd = ft_substr(input, 0, i);
	ft_add_token(token_lst, cmd, type);
	free(cmd);
	return (i);
}
