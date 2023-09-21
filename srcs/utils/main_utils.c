/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/19 19:19:32 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_perror(t_minishell *ms, char *error, int free_flag);
int		ft_everything_is_space(char *str);
void	ft_free_str_array(char **str_array);


int	ft_perror(t_minishell *ms, char *error, int free_flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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

void	ft_free_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (!str_array)
		return ;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}
