/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:44:16 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/07 17:56:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_space(char c);
int	ft_everything_is_space(char *str);
int	ft_len_until_match(char *input, char *match);
int	ft_is_cmd_or_file(t_type type);
int	ft_perror(char *error);

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (YES);
	return (NO);
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

int	ft_len_until_match(char *input, char *match)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(match, input[i]) == NULL)
		i++;
	return (i);
}

int	ft_is_cmd_or_file(t_type type)
{
	if (type == T_OTHER || type == T_QUOTE || type == T_DQUOTE)
		return (YES);
	return (NO);
}

int	ft_perror(char *error)
{
	printf("%s\n", error);
	return (EXIT_FAILURE);
}
