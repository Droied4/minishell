/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 18:37:29 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)av;
	(void)ac;
	(void)env;
	init_shell(&sh);
	sh.exit_status = 0;
	char *e_itoa;
	char *final_str;
	while (1)
	{
		e_itoa = ft_itoa(sh.exit_status);
		final_str = ft_strjoin("╭─ 🏓 PongShell ───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── ", e_itoa);
		final_str = ft_strjoin(final_str, " \n╰─ ");
	


//--------- hacerlo mas bonito


		sh.line = readline(final_str);
		if (!sh.line)
			exit(1);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		parse_all(&sh);
		execute_builtins(&sh, env);
//		ft_free_array(env);
//		env = convert_to_dchar(sh.env); 
		executor(&sh, env);
	print_tokens(sh.tokens);
	//	print_words(sh.words);
	//	print_redir(sh.redir);
		soft_exit(&sh);
	}
	return (0);
}
