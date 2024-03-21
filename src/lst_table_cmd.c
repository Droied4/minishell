/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_table_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:24:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 18:55:21 by avolcy           ###   ########.fr       */
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

static void	create_cmdlst(t_cmds **lst, t_cmds *new)
{
	t_cmds	*last;

	if (!(*lst))
	{
		*lst = new;
		return;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static int	new_table(t_token *tokens)
{
	int	*meta_char;
	int			i;

	meta_char = malloc(sizeof(int) * 8);
	if (!meta_char)
		return (-1);
	i = -1;
	while(++i <= 7)
		meta_char[i] = i;
	if (tokens->prev && tokens->prev->type == CMD && tokens->type == CMD)
	{
		free(meta_char);
		return (-1);
	}
	while (--i >= -1)
	{
		if (tokens->type == CMD || tokens->type == meta_char[i])
		{
			free(meta_char);
			return (1);
		}
	}
	free(meta_char);
	return (-1);
}

int	ft_delcmds(t_cmds **lst)
{
	t_cmds	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		ft_free_array((*lst)->cmd);
		free((*lst)->path);
		free((*lst)->in_file);
		free((*lst)->out_file);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
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