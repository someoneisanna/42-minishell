/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:26:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/02 16:21:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_main_loop(t_minishell *ms);

int	main(int ac, char **av)
{
	t_minishell	ms;

	if (ac > 1 || av[1])
		return (printf("Usage: ./minishell\n"));
	ft_bzero(&ms, sizeof(t_minishell));
	ft_main_loop(&ms);
}

void	ft_main_loop(t_minishell *ms)
{
	while (42)
	{
		ms->input = readline("minishell> ");
		if (!ms->input)
			exit(0);
		add_history(ms->input);
		if (ft_everything_is_space(ms->input) == FALSE)
		{
			ft_parser(ms, ms->input);
			ft_free_token_lst(&ms->token);
		}
		free(ms->input);
	}
	rl_clear_history();
}
