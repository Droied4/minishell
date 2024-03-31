/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:01:28 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 01:18:42 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_token *lst)
{
	if (ft_strncmp(lst->data, "<<", 3) == 0)
		lst->type = DLESS;
	else if (ft_strncmp(lst->data, ">>", 2) == 0)
		lst->type = DGREAT;
	else if (ft_strncmp(lst->data, "<", 1) == 0 || ft_strncmp(lst->data, "<<<",
			3) == 0)
		lst->type = LESS;
	else if (ft_strncmp(lst->data, ">", 1) == 0)
		lst->type = GREAT;
	else if (ft_strncmp(lst->data, "|", 1) == 0)
		lst->type = PIPE;
	else if (ft_strncmp(lst->data, "\'", 1) == 0)
		lst->type = SQUOTE;
	else if (ft_strncmp(lst->data, "\"", 1) == 0)
		lst->type = DQUOTE;
	else if (ft_strncmp(lst->data, "$", 1) == 0)
		lst->type = EXP;
	else
		lst->type = CMD;
}

static int len_of_words(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (is_charmeta(*line) > 0)
	{
		if (is_char_redir(*line) > 0)
			return (lex_redir_case(line, *line));
		else if (*line == '\'' || *line == '\"')
			return (lex_quotes_case(line, *line) + 1);
	}
	return (lex_word_case(line));
}

static char *cpy_words(char **line, char *words, int len_word)
{
	int i;

	i = 0;
	if (*(*line) != '\'' || *(*line) != '\"')
	{
		while (*(*line)&& *(*line) == ' ')
			(*line)++;
	}
	while (i < len_word)
	{
		words[i] = (*line)[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

static char *aux_montage(char **line)
{
	char *words;

	int len_word;

	len_word = len_of_words(*line);
	words = malloc(sizeof(char) * len_word + 1);
	if (!words)
		exit(1);
	words = cpy_words(line, words, len_word);
	*line += len_word;
	return (words);
}

char	**montage_tokens(char *line)
{
	char	**tokens = NULL;
	char 	*words;
	int		len;
	int 	i;
	char	*keeper;
	
	i = 0;
	keeper = line;
	len = len_matriz(line);
	tokens = ft_calloc(sizeof(char *), len + 1);
	if (!tokens)
		exit(1);
	while (len--)
	{
		words = aux_montage(&line);
		tokens[i] = words;
		i++;
	}
	line = keeper;
	return (tokens);
}
