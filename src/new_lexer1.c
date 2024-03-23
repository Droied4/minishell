/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:03:05 by deordone          #+#    #+#             */
/*   Updated: 2024/03/23 17:36:03 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_redir_case(char *s, char redir)
{
	int	max;
	int	i;

	i = 0;
	if (redir == '<')
		max = 4;
	else
		max = 3;
	while (s[i] == redir)
	{
		max--;
		if (max == 0)
			break ;
		i++;
	}
	return (i);
}

int	lex_word_case(char *s)
{
	int	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\0' && (is_charmeta(s[i]) < 0
			|| s[i] == '$'))
		i++;
	return (i);
}

int	lex_quotes_case(char *s, char quote)
{
	int	i;

	i = 0;
	i++;
	while (s[i])
	{
		if (s[i] == quote)
			break ;
		i++;
	}
	return (i);
}

static int	*meta_case(char *line, int count, int i, int *res)
{
	res = malloc(sizeof(int) * 2);
	if (is_char_redir(line[i]) > 0 && ++count)
		i += lex_redir_case(&line[i], line[i]);
	else if ((line[i] == '\'' || line[i] == '\"') && ++count)
	{
		i += lex_quotes_case(&line[i], line[i]);
		if (line[i] == '\0')
		{
			res[0] = i;
			res[1] = count;
			return (res);
		}
		i++;
	}
	res[0] = i;
	res[1] = count;
	return (res);
}

int	len_matriz(char *line)
{
	int	i;
	int	*res;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_charmeta(line[i]) > 0 && line[i] != '$')
		{
			res = meta_case(line, count, i, res);
			i = res[0];
			count = res[1];
			free(res);
		}
		else if (line[i] != ' ' && (is_charmeta(line[i]) < 0 || line[i] == '$')
			&& ++count)
			i += lex_word_case(&line[i]);
		else
			i++;
	}
	return (count);
}
