/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:46:50 by deordone          #+#    #+#             */
/*   Updated: 2024/06/10 14:49:46 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unclosed_entry(t_shell *sh)
{
	char	*new_line;
	char	*new_input;
	char	*last_input;

	new_input = readline(GREEN "\n> " NC);
	new_line = ft_strdup("\n");
	new_input = ft_imp_strjoin(new_line, new_input);
	last_input = add_space(new_input);
	free(new_input);
	sh->line = ft_imp_strjoin(sh->line, last_input);
	ft_deltoken(&sh->tokens);
	sh->tokens = generate_tokens(sh->line);
}

static int	final_check(int squotes, int dquotes)
{
	if ((squotes % 2) != 0)
		return (-1);
	if ((dquotes % 2) != 0)
		return (-1);
	return (0);
}

int	input_unclosed(t_shell *sh)
{
	t_token	*tmp_tok;
	int		squotes;
	int		dquotes;
	int		i;

	tmp_tok = sh->tokens;
	squotes = 0;
	dquotes = 0;
	while (tmp_tok)
	{
		i = -1;
		if (tmp_tok->type == SQUOTE && (dquotes % 2) == 0)
		{
			while (tmp_tok->data[++i])
			{
				if (tmp_tok->data[i] == '\'')
					squotes++;
			}
			i = -1;
		}
		if (tmp_tok->type == DQUOTE && (squotes % 2) == 0)
		{
			while (tmp_tok->data[++i])
			{
				if (tmp_tok->data[i] == '\"')
					dquotes++;
			}
		}
		tmp_tok = tmp_tok->next;
	}
	return (final_check(squotes, dquotes));
}

void	incomplete_entry(t_shell *sh)
{
	char	*new_input;
	char	*last_input;

	new_input = readline(GREEN "\n> " NC);
	if (!new_input)
		return ;
	last_input = add_space(new_input);
	free(new_input);
	sh->line = ft_imp_strjoin(sh->line, last_input);
	ft_deltoken(&sh->tokens);
	sh->tokens = generate_tokens(sh->line);
}

int	input_incomplete(t_shell *sh)
{
	t_token	*tmp_tok;

	tmp_tok = sh->tokens;
	while (tmp_tok)
	{
		if (tmp_tok->type == PIPE && !tmp_tok->next)
			return (-1);
		tmp_tok = tmp_tok->next;
	}
	return (0);
}
