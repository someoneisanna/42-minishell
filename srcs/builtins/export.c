/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/01 16:39:14 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	enter comments here
*/

void	ft_export(t_minishell *ms, t_cmd *cmd_ptr)
{
	(void)ms;
	printf("executing %s\n", cmd_ptr->cmd);
}
