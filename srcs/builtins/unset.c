/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:36:01 by ataboada          #+#    #+#             */
/*   Updated: 2023/11/05 15:52:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_minishell *ms, t_cmd *curr);
void	ft_export_unset(t_minishell *ms, char *arg);
void	ft_unset_unset(t_minishell *m, t_cmd *c, t_env *e, t_env *p);

void	ft_unset(t_minishell *ms, t_cmd *curr)
{
	int		i;
	t_env	*e;
	t_env	*p;

	i = 0;
	e = ms->env_lst;
	p = NULL;
	if(curr->args[1] == NULL)
		return (ft_builtin_error(ms, curr, NULL, 0));
	if (!ft_cmd_has_valid_option(curr->args))
		return (ft_builtin_error(ms, curr, NULL, 2));
	while(curr->args[i])
	{
		if (!ft_args_are_valid(curr->args[i], NO))
			break ;
		i++;
	}
	ft_unset_unset(ms, curr, e, p);
	g_exit_status = 0;
	if (ms->n_pipes != 0)
		exit(0);
}

void	ft_unset_unset(t_minishell *m, t_cmd *c, t_env *e, t_env *p)
{
	int i;

	i = 0;
	while(c->args[++i])
	{
		e = m->env_lst;
		while(e)
		{
			if (!ft_strcmp(c->args[i], e->key))
			{
				if (c->args[i][0] == '=')
					break ;
				if (p == NULL)
					m->env_lst = e->next;
				else
					p->next = e->next;
				free(e->key);
				free(e->value);
				free(e);
				break;
			}
			p = e;
			e = e->next;
		}
	}
}

void	ft_export_unset(t_minishell *ms, char *arg)
{
	t_env	*e;
	t_env	*p;

	e = ms->env_lst;
	p = NULL;
	while (e)
	{
		if (!strncmp(e->key, arg, ft_strmlen(arg, '=')))
		{
			if (ft_strchr(arg, '=') == NULL && e->value)
				break ;
			if (p == NULL)
				ms->env_lst = e->next;
			else
				p->next = e->next;
			free(e->key);
			free(e->value);
			free(e);
			break ;
		}
		p = e;
		e = e->next;
	}
}
