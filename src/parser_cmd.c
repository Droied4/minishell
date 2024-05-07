/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:49:16 by deordone          #+#    #+#             */
/*   Updated: 2024/05/06 14:53:22 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_space(char *info)
{
	char	*s;
	char	*new_s;

	if (info)
	{
		s = ft_strdup(info);
		new_s = ft_strjoin(s, " ");
		free(s);
		return (new_s);
	}
	else
		return (NULL);
}

static void	new_cmd(char **final, t_token *tok)
{
	char	*word;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == CMD || tok->type == SQUOTE || tok->type == DQUOTE)
		{
			len = ft_strlen(tok->data);
			word = malloc(sizeof(char) * len + 1);
			if (!word)
				exit(1);
			ft_strlcpy(word, tok->data, len + 1);
			final[++i] = word;
		}
		tok = tok->next;
	}
}

t_token	*fill_block(t_words **word, t_token *tok)
{
	t_token	*tok2;
	int		count;

	tok2 = tok;
	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == CMD || tok->type == SQUOTE || tok->type == DQUOTE)
			count++;
		tok = tok->next;
	}
	if (count == 0)
	{
		(*word)->cmd = NULL;
		return (tok);
	}
	(*word)->cmd = ft_calloc(sizeof(char *), count + 1);
	if (!(*word)->cmd)
		exit(1);
	new_cmd((*word)->cmd, tok2);
	(*word)->cmd[count] = NULL;
	return (tok);
}
