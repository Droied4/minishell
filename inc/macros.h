/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:17 by deordone          #+#    #+#             */
/*   Updated: 2024/03/06 00:18:36 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/*
 *COLORS
 * */
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;97m"
# define BLUE "\033[0;34m"
# define NC "\033[0m"

# define BUG {\
		dprintf(2, "Ha entrado en -> %s\n", __FILE__);\
		dprintf(2, "En la funcion -> %s\n", __func__);\
		dprintf(2, "En la linea -> %d\n", __LINE__);\
	      }
# define STD_IN 0 
# define STD_OUT 1
# define STR_REDIR "| > <"
# define REDIR {PIPE, GREAT, LESS, DGREAT, DLESS}
# define STR_META "| > < >> << ' $" ""   
# define META {PIPE, GREAT, LESS, DGREAT, DLESS, SQUOTE, DQUOTE, EXP}

/*
 * TOKEN TYPE 
 * */
//# define CMD ""

#endif
