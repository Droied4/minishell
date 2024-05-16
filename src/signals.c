/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:08:18 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/16 16:19:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern volatile sig_atomic_t	g_signal_received;

// extern indicates that the variable g_signal_received is declared elsewhere,
//  usually inanother source file. It informs the compiler that the variable
//  is defined in another file and should be accessed externally.

// volatile : tells the compiler that the value of g_signal_received may change 
// at any time it prevents the compiler from optimizing away accesses to this
// variable and ensures that the variable's value is always read from memory
//  rather than from a cached register.


// sig_atomic_t is just the data type that you are allowed 
// to use in the context of a signal handler,This is a type typically defined
// in the <signal.h> header file. It's specifically designed for variables used 
// in signal handlers. It ensures that read and writeoperations on such 
// variables are atomic, meaning they are indivisible and cannot be interrupted by signals

// SIGINT by default terminates a process and it raises when you press ctrl + C
// but can change the behavior whithin a sighandler function, in minishell 
// ctrl + C displays a new prompt on a new line. 
// ctrl + D exits the shell.
// ctrl + \ does nothing 
typedef enum e_signal
{
    HEREDOC,
    INTERACTIVE,
    NON_INTERACTIVE
}   t_signal;

void    manage_ctrl_c(int signo)
{
    (void)signo;
    ft_dprintf(1,"\n");
    rl_on_new_line();// indicate that a new line has started in the Readline library
    rl_replace_line();
    // typically follows the rl_on_new_line function to
    // inform Readline that the prompt and input buffer have been updated
    // replace the current line (input buffer) with the provided string
    rl_redisplay();
}

void signal_handler_interactive(int signum)
{
    struct sigaction sigint_action;    
    struct sigaction sigquit_action;

    (void)signum;
    sigint_action.sa_handler = &manage_ctrl_c;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);
    sigquit_action.sa_handler = SIG_IGN;
    sigemptyset(&sigquit_action.sa_mask);
    sigquit_action.sa_flags = 0;
    sigaction(SIGQUIT, &sigquit_action, NULL);

}

void    signal_handler_non_interactive(int signum)
{
    struct sigaction sigint_action;
    struct sigaction sigquit_action;

    (void)signum;
    sigint_action.sa_handler = &print_slash_n;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);
    sigquit_action.sa_handler = &print_quit_msg;
    sigemptyset(&sigquit_action.sa_mask);
    sigquit_action.sa_flags = 0;
    sigaction(SIGQUIT, &sigquit_action, NULL);

}

void    signal_handler_herdoc(int signum)
{
    struct sigaction sigint_action;
    struct sigaction sigquit_action;

    (void)signum;
    sigint_action.sa_handler = SIG_IGN;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);
    sigquit_action.sa_handler = SIG_IGN;
    sigemptyset(&sigquit_action.sa_mask);
    sigquit_action.sa_flags = 0;
    sigaction(SIGQUIT, &sigquit_action, NULL);
}

int manage_signals(t_signal mode)
{

}