/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 11:42:51 by deordone         ###   ########.fr       */
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
