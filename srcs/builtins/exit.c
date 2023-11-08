/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:31 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/08 19:49:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_minishell *ms, t_cmd *curr);
int		ft_isnum(char *s);

void	ft_exit(t_minishell *ms, t_cmd *curr)
{
	if (g_exit_status == 1)
		return ;
	if (ms->n_pipes == 0)
		printf("exit\n");
	if (curr->args[1] && ft_isnum(curr->args[1]) == YES && curr->args[2])
		return (ft_builtin_error(ms, curr, E_ARGS, 1));
	if (curr->args[1] && ft_isnum(curr->args[1]) == NO)
	{
		ft_builtin_error(ms, curr, curr->args[1], 2);
		ft_free_all(ms, YES);
	}
	if (curr->args[1] && ft_isnum(curr->args[1]) == YES)
	{
		if (curr->args[1][0] == '-')
			g_exit_status = 256 - ft_atoi(curr->args[1] + 1);
		else
			g_exit_status = ft_atoi(curr->args[1]);
		ft_free_all(ms, YES);
	}
	g_exit_status = 0;
	if (curr->has_heredoc == 1)
		unlink(".heredoc");
	ft_free_all(ms, YES);
}

int	ft_isnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[1] && (s[0] == '-' || s[0] == '+'))
			i++;
		if (ft_isdigit(s[i]) == 0)
			return (NO);
		i++;
	}
	return (YES);
}
