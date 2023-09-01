/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:26:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/01 17:09:34 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_main_loop(t_minishell *ms);
int		ft_everything_is_space(char *str);
void	ft_print_list(t_token *list); //CHECKER

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
			ft_print_list(ms->token); // CHECKER
			ft_free_token_lst(&ms->token);
		}
		free(ms->input);
	}
	rl_clear_history();
}

int	ft_everything_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == NO)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// CHECKER
void	ft_print_list(t_token *list)
{
	t_token	*current;

	current = list;
	while (current)
	{
		printf("content: %s | ", current->content);
		printf("type: %d\n", current->type);
		current = current->next;
	}
}
