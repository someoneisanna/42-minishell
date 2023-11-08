/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 23:08:54 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_perror(t_minishell *ms, char *error, int free_flag, char *cmd);
int	ft_everything_is_space(char *str);

/*
	ft_perror: used to print some error messages along the project.
		* first, we make sure that the message will be printed in the terminal,
		and not in redirection files or pipes by selecting STDERR as standart
		output.
		* E_CMD and E_SYNTAX are errors that have 127 or 2 as exit_status,
		respectively.
		* other errors, unless modified, will have 1 as exit_status.
		* after all that is done, we use ft_free_all to exit minishell, if the
		free_flag is set to YES.

	ft_everything_is_space: used to check if a string is composed only of spaces
	and tabs.
*/

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
