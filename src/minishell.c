/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/04/01 13:03:03 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)av;
	(void)ac;
	sh.env = NULL;
	sh.st_cmd = NULL;
	while (1)
	{
		sh.line = readline(RED "🏓 PongShell ► " NC);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		sh.cmds = generate_tablecmd(sh.tokens);
		parse_all(&sh);
		execute_builtins(&sh, env);
	//	executor(&sh, env);
		print_words(sh.words);
		print_redir(sh.redir);
		ft_del_words(&sh.words);
		// if (sh.tokens)
		ft_deltoken(&sh.tokens);
		ft_delcmds(&sh.cmds);
		free(sh.line);
	}
	return (0);
}

