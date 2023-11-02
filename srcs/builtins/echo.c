/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:32:41 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/02 16:56:42 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_minishell *ms, t_cmd *curr);
int		ft_tilde_expander(t_minishell *ms, t_cmd *curr, int i);
void	ft_print_argument(char *s);

void	ft_echo(t_minishell *ms, t_cmd *curr)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	if (curr->args[1] == NULL)
	{
		printf("\n");
		ft_free_all(ms, YES);
		exit(g_exit_status);
	}
	if (ft_cmd_has_valid_option(curr->args) == FALSE)
		exit(g_exit_status);
	if (curr->args[1][0] == '-' && curr->args[1][1] == 'n')
		i = 1;
	while (curr->args[++i])
	{
		i += ft_tilde_expander(ms, curr, i);
		if (curr->args[i][0] != '~')
			ft_print_argument(curr->args[i]);
		if (curr->args[i + 1])
			printf(" ");
	}
	if (curr->args[1][0] != '-' || curr->args[1][1] != 'n')
		printf("\n");
	ft_free_all(ms, YES);
}

int	ft_tilde_expander(t_minishell *ms, t_cmd *curr, int i)
{
	char	*home;
	char	**args;

	home = ft_find_env(ms->env_lst, "HOME");
	args = curr->args;
	if (args[i][0] != '~')
		return (0);
	if (args[i][1] == '\0')
		printf("%s", home);
	else if (args[i][1] == '-' && (args[i][2] == '\0' || args[i][2] == '/'))
		printf("%s%s", ft_find_env(ms->env_lst, "OLDPWD"), args[i] + 2);
	else if (args[i][1] == '+' && (args[i][2] == '\0' || args[i][2] == '/'))
		printf("%s%s", ft_find_env(ms->env_lst, "PWD"), args[i] + 2);
	else if (args[i][1] == '/')
		printf("%s%s", home, args[i] + 1);
	else
		printf("%s", args[i]);
	if (args[i + 1])
		return (1);
	return (0);
}

void	ft_print_argument(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\\')
			i++;
		printf("%c", s[i]);
		i++;
	}
}
