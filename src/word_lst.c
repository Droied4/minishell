/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:19:42 by deordone          #+#    #+#             */
/*   Updated: 2024/05/03 02:00:41 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_words	*create_block(int i)
{
	t_words	*new;

	new = (t_words *)malloc(sizeof(t_words));
	if (!new)
		return (NULL);
	new->index = i;
	new->path = NULL;
	new->cmd = NULL;
	new->in = STD_IN;
	new->out = STD_OUT;
	new->next = NULL;
	return (new);
}

static void	create_block_lst(t_words **lst, t_words *new)
{
	t_words *last;

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
	if (tok->type == PIPE)
		return (1);
	else if (tok && !tok->next)
		return (1);
	else
		return (0);
	//un besitoooooo
	//<3
}

int	ft_del_words(t_words **lst)
{
	t_words	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		ft_free_array((*lst)->cmd);
		free((*lst)->path);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

t_words	*generate_words(t_token *tokens)
{
	int		i;
	t_words		*lst;
	t_words		*new;
	t_token		*tmp;

	i = -1;
	tmp = tokens;
	lst = NULL;
	while (tmp)
	{
		if (new_table(tmp) > 0)
		{
			new = create_block(++i);
			if (!new)
				ft_del_words(&lst);
			create_block_lst(&lst, new);
		}
		tmp = tmp->next;
	}
	return (lst);
}
