/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:49:16 by deordone          #+#    #+#             */
/*   Updated: 2024/03/21 09:21:54 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	total_type(t_token *tokens, int type)
{
	t_token	*tmp;
	int		total_char;

	tmp = tokens;
	total_char = 0;
	while (tmp)
	{
		if (tmp->type == type)
			++total_char;
		tmp = tmp->next;
	}
	return (total_char);
}

int	is_redir(int type)
{
	int	*redir;
	int			i;
	
	redir = malloc(sizeof(int) * 3);
	if (!redir)
		return (-1);
	i = -1;
	while (++i <= 2)
		redir[i] = i;
	while (--i > -1)
	{
		if (type == redir[i] || type == DGREAT || type == DLESS)
		{
			free(redir);
			return (1);
		}
	}
	free(redir);
	return (-1);
}

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


t_token *fill_block(t_block **block, t_token *token)
{
	t_token *tok;
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

/*
t_token	*fill_cmd(t_block **cmd, t_token *token)
{
	t_token	*tmp_tok;
	char	*new_cmd;
	char	**final_cmd;

	tmp_tok = token;
	if (!tmp_tok)
		return (NULL);
	new_cmd = add_space(tmp_tok->data);
	final_cmd = build_cmd(tmp_tok, new_cmd);
	while (tmp_tok && is_redir(tmp_tok->type) == -1)
		tmp_tok = tmp_tok->next;
	if (final_cmd == NULL)
		return (tmp_tok->next);
	else
		(*cmd)->cmd = final_cmd;
	return (tmp_tok);
}*/
