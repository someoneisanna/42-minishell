/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:58:00 by jmarinho          #+#    #+#             */
/*   Updated: 2023/11/05 19:07:53 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_args_are_valid(char *arg, int export_flag);
int		ft_strmlen(char *s, char match);

bool	ft_args_are_valid(char *arg, int export_flag)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) || (ft_isalnum(arg[i]) == 0 && arg[i] != '_'))
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			if (export_flag == YES)
				printf("minishell: export: '%s': %s\n", arg, E_EXPORT);
			g_exit_status = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	ft_strmlen(char *s, char match)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != match)
		i++;
	return (i);
}
