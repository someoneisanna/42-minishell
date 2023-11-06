/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:26:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/06 18:25:08 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_main_loop(t_minishell *ms);
void	ft_special_handler(char *input);
void	ft_free_all(t_minishell *ms, int exit_flag);

int	g_exit_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	(void)ac;
	if (av[1])
	{
		printf("minishell: %s: no such file or directory\n", av[1]);
		return (1);
	}
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
		ft_signals();
		ms->input = readline("minishell> ");
		if (ms->input == NULL)
			ft_free_all(ms, YES);
		add_history(ms->input);
		ft_special_handler(ms->input);
		if (ft_everything_is_space(ms->input) == FALSE)
		{
			ms->n_pipes = 0;
			if (ft_parser(ms, ms->input) == EXIT_SUCCESS)
			{
				ft_signals_child();
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

void	ft_special_handler(char *input)
{
	if (input[0] == '$' && input[1] == '?')
	{
		if (input[2] == '+' && input[3] == '$' && input[4] == '?')
		{
			printf("%i+%i: command not found\n", g_exit_status, g_exit_status);
			g_exit_status = 127;
		}
	}
}

void	ft_free_all(t_minishell *ms, int exit_flag)
{
	if (ms->input == NULL)
		printf("exit\n");
	free(ms->input);
	ft_free_token_lst(&ms->token_lst);
	ft_free_cmd_lst(&ms->cmd_lst);
	if (exit_flag == YES)
	{
		ft_free_env_lst(&ms->env_lst);
		ft_free_str_array(ms->paths);
		exit (g_exit_status);
	}
}
