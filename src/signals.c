/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:08:18 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/13 18:14:24 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	interactive_sig_handler(int sign)
{
	if (sign == CTRL_C)
	{
		g_signals = 130;
		rl_replace_line("", 0);
		ft_dprintf(2, "\001\n\033[0;31m130\033[0m 🏓 PongShell \n\002");
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	heredoc_sig_handler(int sign)
{
	if (sign == CTRL_C)
	{
		close(0);
		g_signals = 128 + CTRL_C;
		rl_replace_line("", 1);
		ft_dprintf(1, "\n");
		rl_on_new_line();
	}
}

static void	sigquit_handler(int sign)
{
	if (sign == CTRL_BSLASH)
	{
		// g_signals = 128 + CTRL_BSLASH;
		// ft_dprintf(2, "Quit: 3\n");
	}
}

static void	non_interac_sig_handler(int sign)
{
	write(1, "\n", 1);
	if (sign == SIGINT)
	{
		// g_signals = 128 + CTRL_C;
		// signal(SIGINT, SIG_DFL);
	}
}

void	ft_signals(t_signal mode)
{
	if (mode == INTERACTIVE)
	{
		signal(CTRL_C, interactive_sig_handler);
		signal(CTRL_BSLASH, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(CTRL_C, heredoc_sig_handler);
		signal(CTRL_BSLASH, SIG_IGN);
	}
	else if (mode == NON_INTERACTIVE)
	{
		signal(CTRL_C, non_interac_sig_handler);
		signal(CTRL_BSLASH, sigquit_handler);
	}
}

/*extern volatile sig_atomic_t	g_signal_received;

extern indicates that the variable g_signal_received is declared elsewhere,
 usually inanother source file. It informs the compiler that the variable
 is defined in another file and should be accessed externally.

volatile : tells the compiler that the value of g_signal_received may change
at any time it prevents the compiler from optimizing away accesses to this
variable and ensures that the variable's value is always read from memory
 rather than from a cached register.

sig_atomic_t is just the data type that you are allowed
to use in the context of a signal handler,This is a type typically defined
in the <signal.h> header file. It's specifically designed for variables used
in signal handlers. It ensures that read and writeoperations on such
variables are atomic,
	meaning they are indivisible and cannot be interrupted by signals

SIGINT by default terminates a process and it raises when you press ctrl + C
but can change the behavior whithin a sighandler function, in minishell
ctrl + C displays a new prompt on a new line.
ctrl + D exits the shell.
ctrl + \ does nothing */
