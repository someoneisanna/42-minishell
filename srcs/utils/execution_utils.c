/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/18 10:12:28 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_cmd_has_redir(t_cmd *cmd);

int	ft_cmd_has_redir(t_cmd *cmd)
{
	if (cmd->file_in)
		return (YES);
	if (cmd->file_tr)
		return (YES);
	if (cmd->heredoc)
		return (YES);
	if (cmd->file_ap)
		return (YES);
	return (NO);
}
