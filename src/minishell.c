/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/05/21 16:00:00 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t volatile g_signals = 0;

char	*prompt(int exit_status)
{
	char	*e_itoa;
	char	*str;
	char	*final_str;

	e_itoa = ft_itoa(exit_status);
	if (exit_status == 0)
		final_str = ft_strjoin("\001\033[0;32m✔ \033[0m",
				"🏓  PongShell ↴ \002");
	else
	{
		str = ft_strjoin("\001\033[0;31m", e_itoa);
		final_str = ft_strjoin(str, "\033[0m 🏓  PongShell ↴ \002");
		free(str);
	}
	free(e_itoa);
	return (final_str);
}

static void	init_sh(t_shell *sh, char **env)
{
	sh->exit_status = 0;
	sh->env = NULL;
	sh->cmds = NULL;
	sh->pro.w = NULL;
	sh->pro.r = NULL;
	sh->env = create_lst_env(env);
}


int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	char	*prompt_str;

	(void)av;
	(void)ac;
    init_sh(&sh, env);
	while (1)
	{	
		prompt_str = prompt(sh.exit_status);
		ft_dprintf(1, "\001%s\002\n", prompt_str);
		ft_signals(&sh, INTERACTIVE);
		sh.line = readline("");
		if (!sh.line)
			exit(1);
		free(prompt_str);
		add_history(sh.line);
		sh.tokens = generate_tokens(sh.line);
		if (parse_all(&sh) != -1 && ft_strlen(sh.line) > 0)
		{
		//print_tokens(sh.tokens);
		//	print_words(sh.pro.w);
		//	print_redir(sh.pro.r);
			//convert lst_env into char **matriz_env
			if (!sh.matriz_env)
				sh.matriz_env = convert_env_dchar(sh.env, env);
			executor(&sh);
		}
		soft_exit(&sh);
	}
	return (0);
}
