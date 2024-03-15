/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/15 00:27:30 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_shell *sh)
{
	t_token *tmp_tok;

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

void	parse_cmd(t_shell *sh)
{
	t_token *tmp_tok;
	t_block *tmp_cmd;

	tmp_cmd = sh->block;
	tmp_tok = sh->tokens;
	total_pipes(sh, &sh->tokens);
	while (tmp_tok != NULL || tmp_cmd != NULL)
	{
		if (tmp_cmd)
		{
			tmp_tok = fill_cmd(&tmp_cmd, tmp_tok);
			tmp_cmd = tmp_cmd->next; 
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
	// parse_expansor; supongo que toca parsearlo xd
	sh->block = generate_blocks(sh->tokens);
	parse_block(sh);
	print_blocks(sh->block);
	ft_del_blocks(&sh->block);
}
