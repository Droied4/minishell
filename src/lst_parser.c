/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:44:41 by deordone          #+#    #+#             */
/*   Updated: 2024/03/01 16:58:16 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmds	*create_cmd(int i)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->index = i;
	new->path = NULL;
	new->cmd = NULL;
	new->in_file = NULL;
	new->in = STD_IN;
	new->out_file = NULL;
	new->out = STD_OUT;
	new->next = NULL;
	return (new);
}

static t_cmds	*add_cmd2_end(t_cmds *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	create_cmdlst(t_cmds **lst, t_cmds *new)
{
	t_cmds	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = add_cmd2_end(*lst);
	last->next = new;
}

static int	new_table(t_token *tokens)
{
	static int	meta_char[] = META;
	int			i;

	i = 8;
	if (tokens->prev && tokens->prev->type == CMD && tokens->type == CMD)
		return (-1);
	while (--i >= -1)
	{
		if (tokens->type == CMD || tokens->type == meta_char[i])
			return (1);
	}
	return (-1);
}

t_cmds	*generate_tablecmd(t_token *tokens)
{
	int		i;
	t_cmds	*lst;
	t_cmds	*new;
	t_token	*tmp;

	i = -1;
	tmp = tokens;
	lst = NULL;
	while (tmp)
	{
		if (new_table(tmp) > 0)
		{
			new = create_cmd(++i);
			if (!new)
				ft_delcmds(&lst);
			create_cmdlst(&lst, new);
		}
		tmp = tmp->next;
	}
	return (lst);
}
