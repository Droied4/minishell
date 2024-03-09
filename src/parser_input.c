/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:15:46 by deordone          #+#    #+#             */
/*   Updated: 2024/03/09 04:00:41 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_case(t_token *tok)
{
	if (tok->type == PIPE)
	{
		if ((tok->next && is_redir(tok->next->type) > 0) || (tok->prev
				&& is_redir(tok->prev->type) > 0))
		{
			ft_dprintf(2, "Parse error near '%s'\n", tok->data);
			return (-1);
		}
		else
		{
			ft_dprintf(2, "Parse error near '%c%c'\n", tok->data[0], tok->data[1]);
			return (-1);
		}
	}
	return (0);

}

static int	check_great_less_case(t_token *tok)
{
	if (tok->type != PIPE)
	{
		if ((tok->next && is_redir(tok->next->type) > 0) || (tok->prev
				&& is_redir(tok->prev->type) > 0))
		{
			ft_dprintf(2, "Parse error near '%s'\n", tok->next->data);
			return (-1);
		}
		else if (!tok->next)
		{
			ft_dprintf(2, "Parse error near '\\n'\n", tok->data);
			return (-1);
		}
	}
	return (0);
}

int	check_redir(t_token *tok)
{
	while (tok)
	{
		if (is_redir(tok->type) > 0)
		{
			if (check_great_less_case(tok) < 0)
				return (-1);
			if (check_pipe_case(tok) < 0)
				return (-1);
		}
		tok = tok->next;
	}
	return (0);
}
