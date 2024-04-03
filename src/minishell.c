/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/04/03 16:06:25 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt(int exit_status)
{
	char	*e_itoa;
	char	*str;
	char	*final_str;

	e_itoa = ft_itoa(exit_status);
	if (exit_status == 0)
		str = ft_strjoin("\n\033[40m ╭─ 🏓 \033[0;97m PongShell \033[40m  ───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── \033[0m \033[0;32m", " ✔ \033[0m");
	//	str = ft_strjoin("\033[0;32m╭─ 🏓 \033[0;97m PongShell \033[0;32m  ───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── \033[0;32m", "✔");
	else
		str = ft_strjoin("\n\033[40m ╭─ 🏓 \033[0;97m PongShell \033[40m  ───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── \033[0m \033[0;31m",
				e_itoa);
	// str = ft_strjoin("\033[0;32m╭─ 🏓 \033[0;97m PongShell \033[0;32m  ───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────── \033[0;31m", e_itoa);
	final_str = ft_strjoin(str, "\n\033[40m ╰─ \033[0m");
	free(str);
	free(e_itoa);
	return (final_str);
}

int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	char	*prompt_str;

	(void)av;
	(void)ac;
	(void)env;
	sh.exit_status = 0;
	sh.env = NULL;
	sh.cmds = NULL;
	while (1)
	{
		prompt_str = prompt(sh.exit_status);
		sh.line = readline(prompt_str);
		free(prompt_str);
		if (!sh.line)
			exit(1);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		parse_all(&sh);
		execute_builtins(&sh, env);
		//		ft_free_array(env);
		//		env = convert_to_dchar(sh.env);
		executor(&sh, env);
		//print_tokens(sh.tokens);
		//	print_words(sh.words);
		//	print_redir(sh.redir);
		soft_exit(&sh);
	}
	return (0);
}

