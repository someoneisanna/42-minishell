/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:06:37 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 15:23:38 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

void	ft_tokenizer(t_minishell *ms, char *input)
{
	int i;

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
	int i = 0;
	char *cmd;
	int in_squote = 0;
	int in_dquote = 0;

	while (input[i])
	{
		if (input[i] == '\'' && in_dquote == 0)
			in_squote = 1 - in_squote;
		else if (input[i] == '"' && in_squote == 0)
			in_dquote = 1 - in_dquote;
		else if ((input[i] == ' ' || input[i] == '>' || input[i] == '<' || input[i] == '|')
			&& in_squote == 0 && in_dquote == 0)
			break;
		i++;
	}
	cmd = ft_substr(input, 0, i);
	ft_add_token(token_lst, cmd, type);
	free(cmd);
	return (i);
}
