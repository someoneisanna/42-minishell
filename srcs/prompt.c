/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:10:19 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/29 18:11:04 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prompt(t_minishell *ms);

void	ft_prompt(t_minishell *ms)
{
	while (1)
	{
		ms->input = readline("minishell> ");
		if (!ms->input)
			exit(0);
		add_history(ms->input);
		free(ms->input);
	}
}
