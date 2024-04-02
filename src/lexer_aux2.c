/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:51 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 15:42:29 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*aux_squote(t_token *tmp)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != SQUOTE && tmp->type != EXP)
			tmp->type = CMD;
		else if (tmp->type == EXP)
			tmp->type = EXP;
		else
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static t_token	*aux_dquote(t_token *tmp)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != DQUOTE && tmp->type != EXP)
			tmp->type = CMD;
		else if (tmp->type == EXP)
			tmp->type = EXP;
		else
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

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
		else if (tmp->type == SQUOTE)
			tmp = aux_squote(tmp);
		else if (tmp->type == DQUOTE)
			tmp = aux_dquote(tmp);
		if (tmp)
			tmp = tmp->next;
	}
}
