/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:08:18 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/10 14:08:30 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
variables are atomic, meaning they are indivisible and cannot be interrupted by signals

SIGINT by default terminates a process and it raises when you press ctrl + C
but can change the behavior whithin a sighandler function, in minishell 
ctrl + C displays a new prompt on a new line. 
ctrl + D exits the shell.
ctrl + \ does nothing */


/*	disable_control_chars_echo()
 *   
 *  The extra characters ^C and ^\ (a.k.a control characters) are added to the
 *	terminal's input buffer when you press CTRL+C or CTRL+\ to send SIGINT or 
 *	SIGQUIT signals. To prevent these control characters from being displayed 
 *	in minishell's prompt we must configure the terminal to not echo control
 *	characters. This can achieve this by setting the terminal's attributes, 
 *	specifically the ECHOCTL flag, using the termios library in C. 
 */
void	disable_control_chars_echo(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}
void	print_slash_n(int signo)
{
    (void)signo;
	printf("\n");
	rl_on_new_line();
}

	
// both examples display a newline but when we press ctrl + d - it gives a segmentation fault 
//  and when we press ctrl + c - it doesnt cancel the line) ls | "
// You can find this in /minishell/src/parser/parser_entry.c incomplete_entry 
// (for pipe case) and unclosed_entry (for quotes case)
// when we execute our terminal and we press ctrl + d whitout puting an input before we got a segmentation fault)

/*	restore_terminal_settings()
 *
 *	Sets terminal configuration back to the original settings
 */

void	restore_terminal_settings(void)
{
	struct termios	new_termios;	

	tcgetattr(0, &new_termios);
	new_termios.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}

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
		g_signals = 1;
		rl_replace_line("", 1);
		ft_dprintf(2, "\001\n\033[0;31m1\033[0m 🏓 PongShell \n\002");
		rl_on_new_line();
		rl_redisplay();
	}
}
static void sigquit_handler()
{
	g_signals = 128 + CTRL_BSLASH;
	ft_dprintf(2, "Quit: 3\n");
}

static void	non_interac_sig_handler(int sign)
{
	write(1, "\n", 1);
	if (sign == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		g_signals = 128 + CTRL_C;
	}

}

void	ft_signals(t_shell *sh, t_signal mode)
{
	(void)sh;
	if (mode == INTERACTIVE)//perfecto
	{
		signal(CTRL_C, interactive_sig_handler);
		signal(CTRL_BSLASH, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		//ctrl + D gives segfault;
		//heredoc probs, it has to be close when a sigint is passed but it still remain even 
		//if I printf the new prompt like in interactive mode;
		signal(CTRL_C, heredoc_sig_handler);
		signal(CTRL_BSLASH,SIG_IGN);
	}
	else if (mode == NON_INTERACTIVE)
	{
		//works perfectly, ❓frontend ERROR cause it still printing the prompt within the ✅
		// instead of printing the exit status it supposes
		// to change to 130 || 131 depends on the received signal
		signal(CTRL_C, non_interac_sig_handler);
		signal(CTRL_BSLASH, sigquit_handler);
	}
}
