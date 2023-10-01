/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 16:38:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	enter comments here
*/

void	ft_env(t_minishell *ms, t_cmd *cmd_ptr)
{
	(void)ms;
	printf("executing %s\n", cmd_ptr->cmd);
}
