/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:17 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 12:43:19 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to create each new node
t_token	*create_node(char *content)
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
t_token	*add_to_end(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// trying to create the list of tokens
void	create_lst(t_token **lst, t_token *new)
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

void	token_type(t_token *lst)
{
	if (ft_strncmp(lst->data, "<<", 2) == 0)
		lst->type = DLESS;
	else if (ft_strncmp(lst->data, ">>", 2) == 0)
		lst->type = DGREAT;
	else if (ft_strncmp(lst->data, "<", 1) == 0)
		lst->type = LESS;
	else if (ft_strncmp(lst->data, ">", 1) == 0)
		lst->type = GREAT;
	else if (ft_strncmp(lst->data, "|", 1) == 0)
		lst->type = PIPE;
	else if (ft_strncmp(lst->data, "\'", 1) == 0)
		lst->type = SQUOTE;
	else if (ft_strncmp(lst->data, "\"", 1) == 0)
		lst->type = DQUOTE;
	else if (ft_strncmp(lst->data, "-", 1) == 0)
		lst->type = FLAG;
	else if (ft_strncmp(lst->data, "$", 1) == 0)
		lst->type = EXP;
	else
		lst->type = CMD;
}

// trying to create the tokens
t_token	*generate_tokens(char *line)
{
	int		i;
	t_token	*new;
	t_token	*lst;
	char	**input;

	i = -1;
	lst = NULL;
	input = ft_split(line, ' ');
	while (input[++i])
	{
		new = create_node(input[i]);
		if (!new)
			ft_del(&lst);
		new->index = i;
		token_type(new);
		create_lst(&lst, new);
	}
	free(input);
//	printlst(lst);
	return (lst);
}
