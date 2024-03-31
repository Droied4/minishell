/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 01:13:12 by deordone         ###   ########.fr       */
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

void	parse_words(t_shell *sh)
{
	t_token	*tmp_tok;
	t_words	*tmp_words;

	tmp_words = sh->block->words;
	tmp_tok = sh->tokens;
	while (tmp_tok != NULL || tmp_words != NULL)
	{
		if (tmp_words)
		{
			tmp_tok = fill_block(&tmp_words, tmp_tok);
			tmp_words = tmp_words->next;
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
	//parse_expansor(); 
	//remove_quotes();
	sh->block->words = generate_words(sh->tokens);
	parse_words(sh);
}
