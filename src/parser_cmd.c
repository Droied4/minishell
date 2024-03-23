/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:49:16 by deordone          #+#    #+#             */
/*   Updated: 2024/03/23 15:06:18 by deordone         ###   ########.fr       */
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

static char	**build_cmd(t_token *tok, char *new_cmd)
{
	char	**final_cmd;
	char	*flag;

	while (tok && is_meta(tok->type) < 0)
	{
		tok = tok->next;
		if (tok && tok->type == CMD)
		{
			flag = add_space(tok->data);
			new_cmd = ft_imp_strjoin(new_cmd, flag);
		}
		else
		{
			final_cmd = ft_split(new_cmd, ' ');
			free(new_cmd);
			return (final_cmd);
		}
	}
	free(new_cmd);
	return (NULL);
}

t_token	*fill_block(t_block **block, t_token *token)
{
	t_token	*tok;
	char	*new_cmd;
	char	**final_cmd;

	tok = token;
	if (!tok)
		return (NULL);
	new_cmd = add_space(tok->data);
	final_cmd = build_cmd(tok, new_cmd);
	while (tok && is_meta(tok->type) < 0)
		tok = tok->next;
	if (final_cmd == NULL)
		return (tok->next);
	else
		(*block)->cmd = final_cmd;
	return (tok);
}
