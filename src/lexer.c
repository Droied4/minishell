/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:17 by deordone          #+#    #+#             */
/*   Updated: 2024/03/16 00:59:55 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to create each new node
static t_token	*create_node(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// to add the new node to the end of the list
static t_token	*add_to_end(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// trying to create the list of tokens
static void	create_lst(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = add_to_end(*lst);
	last->next = new;
	new->prev = last;
}

int	ft_deltoken(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

static void	token_file(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->type == GREAT || tmp->type == LESS || tmp->type == DGREAT
			|| tmp->type == DLESS)
			tmp->next->type = FILES;
		tmp = tmp->next;
	}
}

t_token	*generate_tokens(char *line)
{
	int		i;
	t_token	*new;
	t_token	*lst;
	char	*line2;
	char	**input;

	i = -1;
	lst = NULL;
	line2 = ft_strtrim(line, " ");
	line2 = add_between(line2, ' ');
	input = ft_split(line2, ' ');
	while (input[++i])
	{
		new = create_node(input[i]);
		if (!new)
			ft_deltoken(&lst);
		new->index = i;
		token_type(new);
		create_lst(&lst, new);
	}
	free(line2);
	free(input);
	token_file(lst);
	print_tokens(lst);
	return (lst);
}
