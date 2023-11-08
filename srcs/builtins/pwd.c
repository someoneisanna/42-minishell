/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/08 19:50:02 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_minishell *ms, t_cmd *curr)
{
	char	cwd[4096];

	if (ft_cmd_has_valid_option(curr->args) == FALSE)
		ft_free_all(ms, YES);
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	g_exit_status = 0;
	ft_free_all(ms, YES);
}
