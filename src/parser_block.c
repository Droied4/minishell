/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:05:31 by deordone          #+#    #+#             */
/*   Updated: 2024/03/20 15:58:27 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	block_type(t_block **block, t_token *tok)
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

static int	s_or_d_quotes(t_block *tmp)
{
	if (tmp->type == B_SQUOTES)
		return (B_SQUOTES);
	else if (tmp->type == B_DQUOTES)
		return (B_DQUOTES);
	else
		return (-1);
}

static void	redir_file_case(t_block *block)
{
	t_block	*tmp;

	tmp = block;
	tmp = tmp->next;
	if (tmp)
	{
		if (tmp->type == B_SQUOTES || tmp->type == B_DQUOTES)
		{
			tmp = tmp->next;
			while (tmp && tmp->type != B_SQUOTES && tmp->type != B_DQUOTES)
			{
				tmp->type = B_FILE;
				tmp = tmp->next;
			
			}
		}
		else
			tmp->type = B_FILE;
	}
}

static void	redifine_block_type(t_shell *sh)
{
	t_block	*tmp;
	int		quotes;

	tmp = sh->block;
	while (tmp)
	{
		if (tmp->next && (tmp->type == B_SQUOTES || tmp->type == B_DQUOTES))
		{
			quotes = s_or_d_quotes(tmp);
			tmp = tmp->next;
			while (tmp && tmp->type != quotes)
			{
				if (tmp->type != B_CMD && tmp->type != quotes)
					tmp->type = B_CMD;
				tmp = tmp->next;
			}
		}
		if (tmp->type == B_REDIR)
			redir_file_case(tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

static void	establish_block_type(t_shell *sh)
{
	t_token	*tmp_tok;
	t_block	*tmp_block;

	tmp_block = sh->block;
	tmp_tok = sh->tokens;
	while (tmp_tok != NULL || tmp_block != NULL)
	{
		if (tmp_block)
		{
			block_type(&tmp_block, tmp_tok);
			if (tmp_tok->type == CMD)
			{
				while (tmp_tok && tmp_tok->type == CMD)
					tmp_tok = tmp_tok->next;
			}
			else
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
	t_token	*tmp_tok;
	t_block	*tmp_block;

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
