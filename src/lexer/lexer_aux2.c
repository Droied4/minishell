/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:51 by deordone          #+#    #+#             */
/*   Updated: 2024/06/14 16:54:56 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redifine_token(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->next && (tmp->type == GREAT || tmp->type == LESS
				|| tmp->type == DGREAT || tmp->type == DLESS))
		{
			if (tmp->next && is_meta(tmp->next->type) < 0)
				tmp->next->type = FILES;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
