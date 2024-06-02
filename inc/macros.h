/* ************************************************************************ */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:17 by deordone          #+#    #+#             */
/*   Updated: 2024/05/31 19:30:10 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
 *COLORS
 * */
# define RED "\001\033[0;31m\002"
# define CYAN "\001\033[0;36m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define WHITE "\001\033[0;97m\002"
# define BLUE "\001\033[0;34m\002"
# define NC "\001\033[0m\002"
# define EXIT_STATUS "127"

# define BUG {\
		dprintf(2, "Ha entrado en -> %s\n", __FILE__);\
		dprintf(2, "En la funcion -> %s\n", __func__);\
		dprintf(2, "En la linea -> %d\n", __LINE__);\
		perror("Error : ");\
	      }
# define SQUOT '\'' 
# define DQUOT '\"'  
# define STD_IN 0 
# define STD_OUT 1
# define DASH_N "-n"
# define STR_REDIR "|s><"
# define CTRL_C SIGINT
# define CTRL_BSLASH SIGQUIT
# define REDIR {PIPE, GREAT, LESS, DGREAT, DLESS}
# define STR_META "|><\'\"$"
# define METACHAR {PIPE, GREAT, LESS, DGREAT, DLESS, SQUOTE, DQUOTE, EXP}
# define STR_BUILTINS "echo cd pwd export unset env exit"
# define NUM_ARG_REQ "numeric argument required\n"
# define TOO_MANY_ARG "Pongshell: exit: too many arguments\n"
# define WRONG_ARG "Dear evaluator\nWe should not consider this case\n"
# define WRONG_ARG_1 "With love...🤓🤓\n🏓PongShell ✌🏼✌🏾\n"
# define SHELL_ERROR "🏓PongShell ERROR !\nTry with a non NULL env\n"

#endif
