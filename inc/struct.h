/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/05/27 15:02:12 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <time.h>
#include "minishell.h"

typedef struct s_token
{
	int							index;
	char						*data;
	int							type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_words
{
	int							index;
	char						**cmd;
	char						*path;
	int							in;//lista de fds 
	int							out;
	struct s_words				*next;
}								t_words;

typedef struct s_redir
{
	int							index;
	int							type;
	char						*file;
	int							fd;
	struct s_redir				*next;
}								t_redir;

typedef struct s_process
{
	struct s_words				*w;
	struct s_redir				*r;
    pid_t                       pid;
    int                         p[2];
    int                         wstatus;
} t_process;

typedef struct s_env
{
	char						*line;
	struct s_env				*next;
    struct s_env				*prev;
	char						*var_name;
	char						*var_content;
}								t_env;

typedef struct s_shell
{
	struct s_process			pro;
	struct s_env				*env;
	int							pipes;
	char						*line;
	struct s_cmds				*cmds;
	struct s_token				*tokens;
	int							exit_status;
	char						**matriz_env;
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
	FILES,  // 8
	CMD     // 9
}								t_type;

typedef enum e_block_type
{
	B_PIPE,    // 0
	B_REDIR,   // 1
	B_BUILT,   // 2
	B_SQUOTES, // 3
	B_DQUOTES, // 4
	B_CMD,     // 5
	B_FILE     // 6
}								t_block_type;

typedef enum e_signal
{
    HEREDOC,
    INTERACTIVE,
    NON_INTERACTIVE
}   t_signal;

#endif
