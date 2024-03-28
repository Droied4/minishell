/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/26 14:45:12 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{

	t_shell sh;

	(void)av;
	(void)ac;
	sh.env = NULL;
	sh.st_cmd = NULL;
	while (1)
	{
		sh.line = readline(RED"🏓 PongShell ► "NC);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		//sh.cmds = generate_tablecmd(sh.tokens);
		//parse_all(&sh);
		execute_builtins(&sh, env);
		// if (sh.tokens)
		ft_deltoken(&sh.tokens);
		// if (sh.cmds)
		// ft_delcmds(&sh.cmds);
		free(sh.line);
	}
	return (0);
}

