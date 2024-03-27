/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/27 14:53:00 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_shell *sh)
{
	t_token	*tmp_tok;

	tmp_tok = sh->tokens;
	while (input_unclosed(sh) < 0)
		unclosed_entry(sh);
	tmp_tok = sh->tokens;
	if (syntax_error(tmp_tok) < 0)
		return (-1);
	while (input_incomplete(sh) < 0)
	{
		incomplete_entry(sh);
		while (input_unclosed(sh) < 0)
			unclosed_entry(sh);
		tmp_tok = sh->tokens;
		if (syntax_error(tmp_tok) < 0)
			return (-1);
	}
	return (0);
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
			tmp_tok = fill_block(&tmp_block, tmp_tok);
			tmp_block = tmp_block->next;
		}
		else
			break ;
	}
}

void	parse_all(t_shell *sh)
{
	if (syntax_error(sh->tokens) < 0)
		return ;
	if (parse_input(sh) < 0)
		return ;
	sh->block = generate_blocks(sh->tokens);
	parse_block(sh);
}
	/* parse_expansor; supongo que toca parsearlo xd*/
