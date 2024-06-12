/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_sig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:34:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/11 21:34:24 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

/*	restore_terminal_settings()
 *	Sets terminal configuration back to the original settings
 */
void	restore_terminal_settings(void)
{
	struct termios	new_termios;

	tcgetattr(0, &new_termios);
	new_termios.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_termios);
}
