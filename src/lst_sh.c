/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:57:24 by deordone          #+#    #+#             */
/*   Updated: 2024/02/15 18:32:43 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	generate_tokens(char *line)
{
	char **input;
	input = ft_split(line, ' ');

	int i = -1;
	while (input[++i])
	{
		new = create_node(input[i]);
		
		create_lst(lst, new);
		printf("%s\n", input[i]);
	}
	return ;
}
