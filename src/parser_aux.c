/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:24:33 by deordone          #+#    #+#             */
/*   Updated: 2024/03/02 16:44:20 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_space(char *info)
{
	char *s;
	char *new_s;
	
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

char **build_cmd(t_token *tmp_tok, char *new_cmd)
{
	char **final_cmd;
	char	*flag;

	while (tmp_tok && is_redir(tmp_tok->type) == -1)
	{
		tmp_tok = tmp_tok->next;
		if (tmp_tok && (tmp_tok->type == FLAG || tmp_tok->type == CMD
				|| tmp_tok->type == ARCH))	// avanzo y miro si el siguiente es un cmd flag o arch
		{
			flag = add_space(tmp_tok->data);
			new_cmd = ft_imp_strjoin(new_cmd, flag); // si lo es lo concateno
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



