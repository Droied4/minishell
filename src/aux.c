/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/02/20 20:01:23 by deordone         ###   ########.fr       */
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
