/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/02/20 19:58:58 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av)
{
	char	*line;
	t_token *tokens;

	(void)av;
	if (ac != 1)
		exit(1);
	while (1)
	{
		line = readline(RED"🏓 PongShell ► "NC);
		//free tokens
		add_history(line);
		tokens = generate_tokens(line);
		free(line);
	}
	return (0);
}
