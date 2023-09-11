/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/09 11:29:54 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_minishell *ms, t_cmd *cmd_ptr)
{
	(void)ms;
	printf("executing %s\n", cmd_ptr->cmd);
}
