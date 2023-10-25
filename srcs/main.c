/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:26:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/24 19:41:01 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_main_loop(t_minishell *ms);
void	ft_free_all(t_minishell *ms, int exit_flag);

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	(void)ac;
	(void)av;
	ft_bzero(&ms, sizeof(t_minishell));
	ms.envp = envp;
	ft_init_env_lst(&ms.env_lst, ms.envp);
	ms.paths = ft_get_paths(ms.env_lst);
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
			ms->n_pipes = 0;
			if (ft_parser(ms, ms->input) == EXIT_SUCCESS)
			{
				ft_executer(ms);
				if (ms->n_pipes > 0)
					ft_free_pipes(ms);
				unlink(".heredoc");
			}
			ft_free_all(ms, NO);
		}
	}
	rl_clear_history();
}

void	ft_free_all(t_minishell *ms, int exit_flag)
{
	free(ms->input);
	ft_free_token_lst(&ms->token_lst);
	ft_free_cmd_lst(&ms->cmd_lst);
	if (exit_flag == YES)
	{
		ft_free_env_lst(&ms->env_lst);
		ft_free_str_array(ms->paths);
		exit (EXIT_SUCCESS); //change to exit status variable
	}
}
