/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/05/06 14:52:08 by deordone         ###   ########.fr       */
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
	sh.pro.w = NULL;
	sh.pro.r = NULL;
	while (1)
	{
		prompt_str = prompt(sh.exit_status);
		sh.line = readline(prompt_str);
		if (!sh.line)
			exit(1);
		free(prompt_str);
		//sh.line = readline("shell -> ");
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		if (parse_all(&sh) != -1 && ft_strlen(sh.line) > 0)
		{
			//print_tokens(sh.tokens);
		//	print_words(sh.pro.w);
		//	print_redir(sh.pro.r);
			sh.matriz_env = env;
			executor(&sh);
		}
		soft_exit(&sh);
	}
	return (0);
}

