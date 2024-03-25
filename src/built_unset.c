/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:36:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/25 14:53:30 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_shell **sh, char **env)
{
	int     i;
	int     pos;
	t_env   *lstenv;
	t_env   *lsttmp;

	i = 0;
	pos = 0;
	if ((*sh)->env == NULL)
		(*sh)->env = create_lst_env(env);
	lstenv = (*sh)->env;
	lsttmp = (*sh)->env;
	if (found_var((*sh)->tokens->next->data, lstenv, &pos))
	{
		while (i < pos && lstenv)
		{
			if (i + 1 == pos)
				break ;
			++i;
			lstenv = lstenv->next;
		}
		lstenv->prev->next = lstenv->next;
		if (lstenv->next)
			lstenv->next->prev = lstenv->prev;
	}
	free(lstenv->line);
	free(lstenv->var_name);
	free(lstenv->line);
	return ;
}