/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:49:16 by deordone          #+#    #+#             */
/*   Updated: 2024/03/05 21:47:07 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	total_pipes(t_shell *sh, t_token **tokens)
{
	t_token	*tmp;
	int		total_pipes;

	tmp = *tokens;
	total_pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			++total_pipes;
		tmp = tmp->next;
	}
	sh->pipes = total_pipes;
}

int	is_redir(int type)
{
	static int	redir[] = REDIR;
	int			i;

	i = 5;
	while (--i >= -1)
	{
		if (type == redir[i])
			return (1);
	}
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
		free(info);
		free(s);
		return (new_s);
	}
	else
		return (NULL);
}

static char	**build_cmd(t_token *tmp_tok, char *new_cmd)
{
	char	**final_cmd;
	char	*flag;

	while (tmp_tok && is_redir(tmp_tok->type) == -1)
	{
		tmp_tok = tmp_tok->next;
		if (tmp_tok && (tmp_tok->type == FLAG || tmp_tok->type == CMD
				|| tmp_tok->type == ARCH))
		{
			flag = add_space(tmp_tok->data);
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

t_token	*fill_cmd(t_cmds **cmd, t_token *token)
{
	t_token	*tmp_tok;
	char	*new_cmd;
	char	**final_cmd;

	tmp_tok = token;
	if (!tmp_tok)
		return (NULL);
	new_cmd = tmp_tok->data;
	new_cmd = add_space(new_cmd);
	final_cmd = build_cmd(tmp_tok, new_cmd);
	while (tmp_tok && is_redir(tmp_tok->type) == -1)
		tmp_tok = tmp_tok->next;
	if (final_cmd == NULL)
		return (tmp_tok->next);
	else
		(*cmd)->cmd = final_cmd;
	return (tmp_tok);
}
