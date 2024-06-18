/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:46:50 by deordone          #+#    #+#             */
/*   Updated: 2024/06/18 12:07:27 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_quote(char *data, int i)
{
	char	quote;

	quote = data[i];
	i++;
	while (data[i])
	{
		if (data[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

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

int	input_unclosed(t_shell *sh)
{
	t_token	*tmp_tok;
	int		i;

	tmp_tok = sh->tokens;
	while (tmp_tok)
	{
		i = -1;
		while (tmp_tok->data[++i])
		{
			if (tmp_tok->data[i] == '\'' || tmp_tok->data[i] == '\"')
				i = next_quote(tmp_tok->data, i);
			if (i == -1)
				return (-1);
		}
		tmp_tok = tmp_tok->next;
	}
	return (0);
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
