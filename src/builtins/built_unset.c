/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:36:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/12 19:22:52 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_shell **sh, t_env *node, char **env)
{
	t_env   *left;
	t_env   *right;
	
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
	free(node->line);
	free(node->var_name);
	free(node->var_content);
	free(node);
}
