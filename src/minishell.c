/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/14 23:57:29 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{

	t_shell sh;

	(void)av;
	(void)ac;
	init_shell(&sh);
	while (1)
	{
		sh.line = readline(RED"🏓 PongShell ► "NC);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		parse_all(&sh);
		execute_builtins(&sh, env);
		ft_deltoken(&sh.tokens);
		//ft_delcmds(&sh.cmds);
		free(sh.line);
	}
	return (0);
}
