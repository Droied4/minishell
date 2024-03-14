/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/03/14 16:05:25 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int							index;
	char						*data;
	int							type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_execution_block
{
	int							index;
	int							type;
	char						**cmd;
	char						*path;
	int							in;
	int							out;
	struct s_execution_block	*next;
}								t_block;

typedef struct s_env
{
	char *line; // for test purpose
	char						*var_name;
	char						*var_content;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	char						*line;
	struct s_token				*tokens;
	struct s_execution_block	*cmds;
	struct s_env				*env;
	struct s_cmds				*st_cmd;
	int							pipes;
}								t_shell;

typedef enum e_type
{
	PIPE,   // 0
	GREAT,  // 1
	LESS,   // 2
	DGREAT, // 3
	DLESS,  // 4
	SQUOTE, // 5
	DQUOTE, // 6
	EXP,    // 7
	CMD     // 8
}								t_type;

#endif
