/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/03/08 20:57:27 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	//t_env	*s_env;
	//char	*line;
	
	(void)av;
	(void)ac;
	init_shell(&sh);
	while (1)
	{
		// if I had the line variable in the struct in order to free it after
		sh.line = readline(RED"🏓 PongShell ► "NC);
		if (!ft_strncmp("🏓 PongShell ► ", sh.line, 15))//to solve enter
			return (1);//not working as expected but will figured it out soon
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		printlst(sh.tokens);
		execute_builtins(&sh, env);
		if (sh.line)
			free(sh.line);
	}
	return (0);
}
