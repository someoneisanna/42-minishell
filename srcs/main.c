/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:26:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/05 10:13:29 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_main_loop(t_minishell *ms);
void	ft_free_all(t_minishell *ms, int exit_flag);

/*
	This is the beginning of the program.
	We initialize the main structure and start the main loop.
	Cronologically, minishell uses the files/folders in this order:
		1) main.c
		2) environment
		2) parser.c
		3) lexical_analysis
		4) syntactic_analysis
		5) expansions
*/

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	(void)ac;
	(void)av;
	ft_bzero(&ms, sizeof(t_minishell));
	ft_init_env_lst(&ms.env, envp);
	ft_main_loop(&ms);
}

void	ft_main_loop(t_minishell *ms)
{
	while (42)
	{
		ms->input = readline("minishell> ");
		if (!ms->input)
			ft_free_all(ms, YES);
		add_history(ms->input);
		if (ft_everything_is_space(ms->input) == FALSE)
		{
			ft_parser(ms, ms->input);
			ft_free_all(ms, NO);
		}
		free(ms->input);
	}
	rl_clear_history();
}

void	ft_free_all(t_minishell *ms, int exit_flag)
{
	ft_free_token_lst(&ms->token);
	if (exit_flag == YES)
	{
		ft_free_env_lst(&ms->env);
		exit (EXIT_SUCCESS); //change to exit status variable
	}
}
