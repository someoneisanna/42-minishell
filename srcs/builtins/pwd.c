/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/31 15:03:44 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_cmd *curr)
{
	char	cwd[4096];

	if (ft_cmd_has_valid_option(curr->args) == FALSE)
		exit(g_exit_status);
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	g_exit_status = 0;
	exit(g_exit_status);
}
