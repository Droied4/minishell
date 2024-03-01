/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/03/01 18:45:56 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to print the list of tokens
void	printlst(t_token *lst)
{
	t_token *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("\nToken %i\n", tmp->index);
		printf("data----%s\n", tmp->data);
		printf("type----%i\n", tmp->type);
		printf("curr----%p\n", tmp);
		printf("prev----%p\n", tmp->prev);
		printf("next----%p\n", tmp->next);
		tmp = tmp->next;
	}
}

void    print_lst_env(t_env *lst, int i)
{
    t_env *tmp;
    
    tmp = lst;
	if (1 == i)
	{
		while (tmp)
		{
        	printf("%s\n", tmp->line);
        	// printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        	// printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        	// printf("next----%p\n", (void *)tmp->next);
        	i++;
        	tmp = tmp->next;
		}
	}
	else if (2 == i)
	{
		while (tmp)
		{
        	printf("declare -x %s\n", tmp->line);
        	// printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        	// printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        	// printf("next----%p\n", (void *)tmp->next);
        	i++;
        	tmp = tmp->next;
		}
	}
}

int	ft_del(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

int	ft_del_env(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->line);
		free((*lst)->var_name);
		free((*lst)->var_content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}