/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:36:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/10 20:24:02 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_shell **sh, char **env)
{
	t_env   *left;
	t_env   *right;
	t_env   *node;

	if ((*sh)->env == NULL)
		(*sh)->env = create_lst_env(env);
	node = found_var((*sh)->tokens->next->data, (*sh)->env);
	if (!node)
		return ;
	left = node->prev;
	right = node->next;
	if (!left)
	{
		(*sh)->env = right;
		(*sh)->env->prev = NULL;
	}
	else
	{
		left->next = right; 
		if (right)
			right->prev = left;
	}
	ft_del_env(&node);
	// free(node->line);
	// free(node->var_name);
	// free(node->var_content);
	// free(node);
}
