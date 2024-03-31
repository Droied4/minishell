/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:19:42 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 01:20:37 by deordone         ###   ########.fr       */
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

static int	new_table(t_token *tok, int aux)
{
	if ((aux == 0 || aux == -2) && (tok->type == CMD || tok->type == SQUOTE || tok->type == DQUOTE))
		return (1);
	else if (aux == -2)
		return (-2);
	else if (tok->type == PIPE)
		return (0);
	return (-1);
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
	int		aux;
	t_words	*lst;
	t_words	*new;
	t_token	*tmp;

	i = -1;
	aux = -2;
	tmp = tokens;
	lst = NULL;
	while (tmp)
	{
		aux = new_table(tmp, aux);
		if (aux > 0)
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
