/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:36:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/21 20:08:16 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env **node)
{
	free((*node)->line);
	free((*node)->var_name);
	free((*node)->var_content);
	free(*node);
}

static int check_data(char *str)
{
  int i;
  int flag; 

  i = 0;
  flag = 1;
  if (!ft_isalpha(str[0]))
    return (-1);
  else 
    while (ft_isalnum(str[i]) || str[i] == '_')
      i++;
  if (str[i])
    return (-1);
  return (flag);
}

void	execute_unset(t_shell **sh, t_env *node, char **env)
{
	char	*data;
	t_env	*left;
	t_env	*right;

	if ((*sh)->env == NULL)
		(*sh)->env = create_lst_env(env);
	data = (*sh)->tokens->next->data;
  if(check_data(data) == 1)
	  node = found_var(data, (*sh)->env, ft_strlen(data), NULL);
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
	free_node(&node);
}
