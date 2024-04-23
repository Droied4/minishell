/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/04/22 17:37:28 by avolcy           ###   ########.fr       */
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

int	parse_redirections(t_shell *sh)
{
	t_token	*tmp_tok;
	t_redir *tmp_redir;

	tmp_tok = sh->tokens;
	tmp_redir = sh->redir;
	if (!tmp_tok || !tmp_redir)
		return (1);
	montage_redirections(tmp_tok, tmp_redir);
	if (stock_of(sh, DLESS) > 16)
	{
		ft_dprintf(2, "Error : maximum here-document count exceeded");
		return (-1);
	}
	return (0);
}

void	parse_words(t_shell *sh)
{
	t_token	*tmp_tok;
	t_words	*tmp_words;

	tmp_tok = sh->tokens;
	tmp_words = sh->words;
	while (tmp_tok != NULL && tmp_words != NULL)
	{
		tmp_tok = fill_block(&tmp_words, tmp_tok);
		if (tmp_words->cmd)
			tmp_words = tmp_words->next;
	}
}

int	parse_all(t_shell *sh, char **env)	
{
	if (syntax_error(sh->tokens) < 0)
		return (-1);
	if (parse_input(sh) < 0)
		return (-1);
	expansor(sh, env); 
	//remove_quotes();
	sh->pipes = stock_of(sh, PIPE);
	sh->words = generate_words(sh->tokens);
	parse_words(sh);
	sh->redir = generate_redirs(sh->tokens);
	if (parse_redirections(sh) == -1)
		return (-1);
	return (0);
}
