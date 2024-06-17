/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/06/14 00:04:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t volatile	g_signals = 0;

void	ft_itos(int entero, char *new_level)
{
	if (entero < 10)
	{
		new_level[0] = entero + '0';
		new_level[1] = '\0';
	}
	else if (entero < 100)
	{
		new_level[0] = (entero / 10) + '0';
		new_level[1] = (entero % 10) + '0';
		new_level[2] = '\0';
	}
	else if (entero < 1000)
	{
		new_level[0] = (entero / 100) + '0';
		entero = entero % 100;
		new_level[1] = (entero / 10) + '0';
		new_level[2] = (entero % 10) + '0';
		new_level[3] = '\0';
	}
}

char	*prompt(int exit_status)
{
	static char	str[256];
	char		entero[5];

	ft_itos(exit_status, entero);
	if (exit_status == 0)
		ft_strlcpy(str, "\001\033[0;32m✔ \033[0m 🏓 PongShell \002",
			sizeof(str));
	else
	{
		ft_strlcpy(str, "\001\033[0;31m", sizeof(str));
		ft_strlcat(str, entero, sizeof(str));
		ft_strlcat(str, "\033[0m 🏓 PongShell \002", sizeof(str));
	}
	return (str);
}

static void	init_sh(t_shell *sh, char **env)
{
	sh->exit_status = 0;
	sh->env = NULL;
	sh->cmds = NULL;
	sh->pro.w = NULL;
	sh->pro.r = NULL;
	sh->tokens = NULL;
	if (!*env)
	{
		ft_dprintf(2, SHELL_ERROR);
		exit(EXIT_FAILURE);
	}
	sh->env = create_lst_env(env);
	sh->matriz_env = NULL;
}

static void	forwarding_process(t_shell *sh, char **env)
{
	sh->tokens = generate_tokens(sh->line);
	if (parse_all(sh) != -1 && ft_strlen(sh->line) > 0)
	{
		sh->matriz_env = convert_env_dchar(sh->env, env, 0);
		restore_terminal_settings();
		executor(sh);
		free_matrix(&sh->matriz_env);
	}
	soft_exit(sh);
}

/*echo $USER""'hello*/
int	main(int ac, char **av, char **env)
{
	t_shell	sh;
	char	*prompt_str;

	(void)av;
	ft_isalpha(0);
	if (ac == 1)
	{
		init_sh(&sh, env);
		while (1)
		{
			prompt_str = prompt(sh.exit_status);
			ft_dprintf(2, "\001%s\002\n", prompt_str);
			ft_signals(INTERACTIVE);
			disable_control_chars_echo();
			sh.line = readline("↳ ");
			if (!sh.line)
				execute_exit(&sh);
			add_history(sh.line);
			forwarding_process(&sh, env);
		}
	}
	else
		ft_dprintf(2, WRONG_ARG, WRONG_ARG_1);
	return (0);
}
