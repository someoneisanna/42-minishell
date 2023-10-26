/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/26 15:15:42 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_perror(t_minishell *ms, char *error, int free_flag, char *file);
int		ft_everything_is_space(char *str);

int	ft_perror(t_minishell *ms, char *error, int free_flag, char *file)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if(!ft_strncmp(error, E_CMD, 19))
		printf("%s: %s\n", ms->cmd_lst->cmd, error);
	else if(!ft_strncmp(error, E_FILE, 27))
		printf("minishell: %s: %s\n", file, error);
	else if(error)
		printf("minishell: %s\n", error);
	if (ms->n_pipes > 0)
		ft_free_pipes(ms);
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
