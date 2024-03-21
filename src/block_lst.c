/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:24:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/21 09:23:12 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_block	*create_block(int i)
{
	t_block	*new;

	new = (t_block *)malloc(sizeof(t_block));
	if (!new)
		return (NULL);
	new->index = i;
	new->type = -1;
	new->path = NULL;
	new->cmd = NULL;
	new->in = STD_IN;
	new->out = STD_OUT;
	new->next = NULL;
	return (new);
}

static void	create_block_lst(t_block **lst, t_block *new)
{
	t_block	*last;

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

static int	new_table(t_token *tokens)
{
	int	*meta_char;
	int	i;

	meta_char = malloc(sizeof(int) * 9);
	if (!meta_char)
		return (-1);
	i = -1;
	while (++i <= 8)
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

int	ft_del_blocks(t_block **lst)
{
	t_block	*temp;

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

t_block	*generate_blocks(t_token *tokens)
{
	int		i;
	t_block	*lst;
	t_block	*new;
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
				ft_del_blocks(&lst);
			create_block_lst(&lst, new);
		}
		tmp = tmp->next;
	}
	return (lst);
}
