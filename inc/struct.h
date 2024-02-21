/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 12:43:12 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int		index;
	char	*data;
	int		type;
	struct s_token *next;
	struct s_token *prev;
}		t_token;

typedef struct s_cmds
{
	char **cmd;
	char *path;
	int	in;
	int	out;
	int err;
	struct s_cmds *next;
}	t_cmds;
/*LA RAZON POR LA QUE CREE ESTO ES PARA TENER UNA ESTRUCTURA 
 * GENERAL EN LA QUE LLEVEMOS TODO COMO LA LISTA DE LAS TOKENS Y LA LISTA DE
 * LOS COMANDOS Y EN UN FUTURO SABER LA CANTIDAD DE PIPES TOTAL O EL EXPANSOR
 * O EL ENV COSAS ASI
 * */

typedef struct s_shell
{
	struct s_token	*tokens;
	struct s_cmds	*cmds;
	int pipes;
}	t_shell;

typedef enum e_type
{
	PIPE,//0
	GREAT,//1
	LESS,//2
	DGREAT,//3
	DLESS,//4
	CMD,//5
	FLAG,//6
	ARCH,//7
	SQUOTE,//8
	DQUOTE,//9
	EXP//10
}		t_type;

#endif
