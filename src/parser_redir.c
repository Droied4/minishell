/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 05:37:11 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *define_file(t_token *tok)
{
	if (tok->type > PIPE && tok->type < SQUOTE)
	{
		if (tok->next)
			return(ft_strdup(tok->next->data));	
	}
	return (NULL);
}

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
		return (-1);
}

void montage_redirections(t_token *tok, t_redir *redir)
{
	while(tok && redir)
	{
		redir->type = define_type(tok);
		redir->file = define_file(tok);
		if (redir->type >= 0)
			redir = redir->next;
		tok = tok->next;
	}
}
