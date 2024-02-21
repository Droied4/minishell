/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 12:02:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{
	char	*line;
	t_shell sh;

	(void)av;
	(void)env;
	if (ac != 1)
		exit(1);
	while (1)
	{
		line = readline(RED"🏓 PongShell ► "NC);
		add_history(line);
		sh.tokens = generate_tokens(line);
		parse_all(&sh);
		ft_del(&sh.tokens);
		free(line);
		if (ft_strncmp(line, "EXIT", 4) == 0)
			exit(0);
	}
	return (0);
}
