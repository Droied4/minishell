/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/05/10 20:48:42 by avolcy           ###   ########.fr       */
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
		final_str = ft_strjoin("\001\033[0;32m✔ \033[0m", "🏓  PongShell ↴ \002");
	else
	{
		str = ft_strjoin("\001\033[0;31m", e_itoa);
		final_str = ft_strjoin(str ,"\033[0m 🏓  PongShell ↴ \002");
		free(str);
	}
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
	sh.env = create_lst_env(env);
	while (1)
	{
		// where does the builtins are called
		prompt_str = prompt(sh.exit_status);
		printf("\001%s\002\n", prompt_str);
		sh.line = readline("");
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
			sh.matriz_env = convert_env_dchar(sh.env, env);//convert lst_env into char **matriz_env
			executor(&sh);
		}
		soft_exit(&sh);
	}
	return (0);
}

