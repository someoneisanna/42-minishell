/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/03 14:57:43 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_perror(t_minishell *ms, char *error, int free_flag, char *cmd);
int	ft_everything_is_space(char *str);

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
		ft_free_all(ms, YES);
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
