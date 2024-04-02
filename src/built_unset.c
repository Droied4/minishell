/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:36:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/02 20:45:46 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env *delete_first(t_env *node)
{
	t_env *lst;

	if (!node)
		return (NULL);
	lst = node->next;
	lst->prev = NULL;
	// free(node->line);
	// free(node->var_name);
	// free(node->var_content);
	// free(node);
	return (lst);
}

void	execute_unset(t_shell **sh, char **env)
{
	int     i;
	int     pos;
	t_env   *lstenv;

	i = 0;
	pos = 0;
	if ((*sh)->env == NULL)
		(*sh)->env = create_lst_env(env);
	lstenv = (*sh)->env;
	if (found_var((*sh)->tokens->next->data, lstenv, &pos))
	{
		if (pos == 1)
			lstenv = delete_first(lstenv);
		else
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
	}
	return ;
}