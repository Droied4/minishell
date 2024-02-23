/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/02/23 17:20:37 by deordone         ###   ########.fr       */
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
		//display_env(env);
		sh.cmds = generate_tablecmd(sh.tokens);
		parse_all(&sh);
		ft_deltoken(&sh.tokens);
		ft_delcmds(&sh.cmds);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(0);
		}
		free(line);
	}
	return (0);
}
