/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:58:00 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/03 13:15:05 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_input_has_heredoc(t_minishell *ms);
bool	ft_cmd_has_valid_option(char **args);
bool	ft_args_are_valid(char *arg);

bool	ft_input_has_heredoc(t_minishell *ms)
{
	t_token	*token;

	token = ms->token_lst;
	while (token)
	{
		if (ft_strncmp(token->content, "<<", 3) == 0)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

bool	ft_cmd_has_valid_option(char **args)
{
	if (args[1] && !ft_strcmp(args[0], "cd"))
	{
		if (args[1][0] == '-' && ft_strlen(args[1]) == 1)
			return (TRUE);
		if (args[1][0] == '-' && args[1][1] == '-' && ft_strlen(args[1]) == 2)
			return (TRUE);
	}
	if (args[1])
	{
		if (args[1][0] == '-')
		{
			if (!ft_strcmp(args[0], "echo")
				&& (args[1][1] != 'e' && args[1][1] != 'E'))
				return (TRUE);
			g_exit_status = 2;
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: -%c: invalid option\n", args[0], args[1][1]);
			return (FALSE);
		}
	}
	return (TRUE);
}

bool	ft_args_are_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) || (!ft_isalnum(arg[i]) && arg[i] != '_'))
		{
			printf("minishell: %s: not a valid identifier\n", arg);
			g_exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
