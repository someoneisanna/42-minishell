/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/09 21:33:54 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_perror(t_minishell *ms, char *error, int free_flag, char *cmd);
int	ft_everything_is_space(char *str);
int	ft_count_redir(t_token *first, t_type type, t_type type2);

int	ft_perror(t_minishell *ms, char *error, int free_flag, char *cmd)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (error && !ft_strcmp(error, E_CMD))
		printf("%s: %s\n", cmd, error);
	else if (error)
	{
		g_exit_status = 1;
		if (!ft_strcmp(error, E_HEREDOC))
			printf("minishell: %s (wanted '%s')\n", E_HEREDOC, cmd);
		else
			printf("minishell: %s\n", error);
		if (!ft_strcmp(error, E_SYNTAX))
			g_exit_status = 2;
	}
	if (free_flag == YES)
		ft_free_all(ms, NO, YES);
	return (EXIT_FAILURE);
}

int	ft_everything_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]) == NO)
			return (FALSE);
		i++;
	}
	return (TRUE);
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
