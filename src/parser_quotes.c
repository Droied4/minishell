/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:46:50 by deordone          #+#    #+#             */
/*   Updated: 2024/03/15 00:14:21 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_quotes(t_shell *sh)
{
	t_token *tmp_tok;
	
	tmp_tok = sh->tokens;
	
	while (tmp_tok)
	{
		if (tmp_tok->type == SQUOTE)
			return (1);
		else if (tmp_tok->type == DQUOTE)
			return (2);
		tmp_tok = tmp_tok->next; 
	}
	return (-1);
}

static int is_closed(int squotes, int dquotes, t_shell *sh)
{
	int quotes;
	quotes = first_quotes(sh);

	if (quotes == -1)
		return (0);
	else if (quotes == 1)
	{
		if ((squotes % 2) != 0)
			return (-1);
	}
	else
	{
		if ((dquotes % 2) != 0)
			return (-1);
	}
	return (0);
}

int	input_unclosed(t_shell *sh)
{
	t_token *tmp_tok;
	int squotes;
	int dquotes;

	tmp_tok = sh->tokens;
	squotes = 0;
	dquotes = 0;
	while (tmp_tok)
	{
		if (tmp_tok->type == SQUOTE && ft_strlen(tmp_tok->data) == 1)
			squotes++;
		else if (tmp_tok->type == DQUOTE && ft_strlen(tmp_tok->data) == 1)
			dquotes++;
		tmp_tok = tmp_tok->next;
	}
	if (is_closed(squotes, dquotes, sh) < 0)
		return (-1);
	return (0);
}

void	unclosed_entry(t_shell *sh)
{
	char *new_line;
	char *new_input;
	char *last_input;

	new_input = readline(GREEN"\n> "NC);
	new_line = ft_strdup("\n");
	new_input = ft_imp_strjoin(new_line, new_input);
	last_input = add_space(new_input);
	free(new_input);
	sh->line = ft_imp_strjoin(sh->line, last_input);
	ft_deltoken(&sh->tokens);
	sh->tokens = generate_tokens(sh->line);
}
