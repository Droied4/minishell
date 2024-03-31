/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:19:06 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 03:14:57 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*create_block(int i)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->index = i;
	new->type = -1;
	new->file = NULL;
	new->fd = -1;
	new->next = NULL;
	return (new);
}

static void	create_block_lst(t_redir **lst, t_redir *new)
{
	t_redir *last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static int	new_table(t_token *tok)
{
	if (is_redir(tok->type) > 0)
		return (1);
	return (-1);
}

int	ft_del_redirs(t_redir **lst)
{
	t_redir	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->file);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

t_redir	*generate_redirs(t_token *tokens)
{
	int		i;
	t_redir	*lst;
	t_redir	*new;
	t_token	*tmp;

	i = -1;
	tmp = tokens;
	lst = NULL;
	while (tmp)
	{
		if (new_table(tmp) > 0)
		{
			new = create_block(++i);
			if (!new)
				ft_del_redirs(&lst);
			create_block_lst(&lst, new);
		}
		tmp = tmp->next;
	}
	return (lst);
}
