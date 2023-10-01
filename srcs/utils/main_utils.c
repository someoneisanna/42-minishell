/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 12:06:07 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_perror(t_minishell *ms, char *error, int free_flag);
int		ft_perror_fd(t_minishell *ms, char *filename, t_type file_type);
int		ft_everything_is_space(char *str);

int	ft_perror(t_minishell *ms, char *error, int free_flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (ms->n_pipes > 0)
		ft_free_pipes(ms);
	if (free_flag == YES)
		ft_free_all(ms, YES);
	return (EXIT_FAILURE);
}

int	ft_perror_fd(t_minishell *ms, char *filename, t_type file_type)
{
	int	fd;

	fd = 0;
	if (file_type == T_FILE_IN)
		fd = open(filename, O_RDONLY);
	else if (file_type == T_FILE_TRUNC)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file_type == T_FILE_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_perror(ms, E_FILE, NO);
		ms->file_error = YES;
		return (EXIT_FAILURE);
	}
	else
		close(fd);
	return (0);
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
