/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 03:23:57 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int define_type(t_token *tok)
{
	if (tok->type == PIPE)
		return (PIPE);
	else if (tok->type == GREAT)
		return (GREAT);
	else if (tok->type == LESS)
		return (LESS);
	else if (tok->type == DGREAT)
		return (DGREAT);
	else if (tok->type == DLESS)
		return (DLESS);
	else
	{
		write(2, "\nhi\n", 4);
		return (-2);
	}
}

void montage_redirections(t_token *tok, t_redir *redir)
{
	while(tok != NULL || redir != NULL)
	{
		write(2, "\nhi\n", 4);
		redir->type = define_type(tok);
		if (redir->type > 0)
			redir = redir->next;
		tok = tok->next;
	}
}
