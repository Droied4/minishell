/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:05:31 by deordone          #+#    #+#             */
/*   Updated: 2024/03/15 14:16:55 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void block_type(t_block **block, t_token *tok)
{
	if (tok->type == PIPE)
		(*block)->type = B_PIPE;
	else if (is_redir(tok->type) > 0)
		(*block)->type = B_REDIR;
	else if (is_builtin(tok->data) > 0)
		(*block)->type = B_BUILT;
	else if (tok->type == SQUOTE)
		(*block)->type = B_SQUOTES;
	else if (tok->type == DQUOTE)	
		(*block)->type = B_DQUOTES;
	else
		(*block)->type = B_CMD;
}

static int s_or_d_quotes(t_shell *sh)
{
	int quotes;

	quotes = first_quotes(sh);
	if (quotes == 1)
		 return(B_SQUOTES);
	else if (quotes == 2)
		 return(B_DQUOTES);
	else
		 return(-1);
}

static void redifine_block_type(t_shell *sh)
{
	t_block *tmp;
	int quotes;

	quotes = s_or_d_quotes(sh);
	tmp = sh->block;
	while (tmp)
	{
		if (tmp->next && tmp->type == B_REDIR)
			tmp->next->type = B_FILE;	
		if (tmp->next && tmp->type == quotes)
		{
			tmp = tmp->next;	
			while (tmp->type != quotes)
			{
				if (tmp->type != B_CMD)
					tmp->type = B_CMD;
				tmp = tmp->next;	
			}
		}
		tmp = tmp->next;
	}
}

static void establish_block_type(t_shell *sh)
{
	t_token *tmp_tok;
	t_block *tmp_block;

	tmp_block = sh->block;
	tmp_tok = sh->tokens;
	while (tmp_tok != NULL || tmp_block != NULL)
	{
		if (tmp_block)
		{
			block_type(&tmp_block, tmp_tok);
			tmp_tok = tmp_tok->next;
			tmp_block = tmp_block->next;
		}
		else
			break ;
	}	
	redifine_block_type(sh);
}

void	parse_block(t_shell *sh)
{
	t_token *tmp_tok;
	t_block *tmp_block;

	tmp_block = sh->block;
	tmp_tok = sh->tokens;
	establish_block_type(sh);
	while (tmp_tok != NULL || tmp_block != NULL)
	{
		if (tmp_block)
		{
		//	tmp_tok = fill_block(&tmp_block, tmp_tok);
			tmp_block = tmp_block->next;
		}
		else
			break ;
	}
}
