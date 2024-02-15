/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:57:24 by deordone          #+#    #+#             */
/*   Updated: 2024/02/15 21:25:49 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to create each new node
t_token	*create_node(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->data = content;
	new->next = NULL;
	return (new);
}

//to add the new node to the end of the list
t_token	*add_to_end(t_token *lst)
{
	printf("hey end\n");
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//trying to create the list of tokens 
void	create_lst(t_token **lst, t_token *new)
{
	t_token	*last;
//SEGFAULT HERE ⁉️
//	printf("hey no lst\n");
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	printf("hey no lst\n");
	last = add_to_end(*lst);
	last->next = new;
}

//to print the list of tokens
static void	printlst(t_token *lst)
{
	while (lst)
	{
		printf("%s\n", lst->data);
		lst = lst->next;
	}
}

//trying to create the tokens 
void	generate_tokens(char *line)
{
	int		i;
	t_token	*new;
	t_token	**lst;
	char	**input;
	
	i = -1;
	lst = NULL;
	input = ft_split(line, ' ');
	while (input[++i])
	{
		new = create_node(input[i]);
		create_lst(lst, new);
	}
	printlst(new);
	return ;
}
