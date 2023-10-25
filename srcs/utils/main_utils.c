/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/25 15:24:40 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_perror(t_minishell *ms, char *error, int free_flag);
int		ft_everything_is_space(char *str);

int	ft_perror(t_minishell *ms, char *error, int free_flag)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
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
