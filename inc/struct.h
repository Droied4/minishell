/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:44:23 by deordone          #+#    #+#             */
/*   Updated: 2024/04/24 18:22:41 by avolcy           ###   ########.fr       */
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

typedef struct s_env
{
	char *line; // for test purpose
	char						*var_name;
	char						*var_content;
	struct s_env				*next;
    struct s_env *prev;
}								t_env;

typedef struct s_shell
{
	char						*line;
	int							exit_status;
	struct s_token				*tokens;
	struct s_words				*words;
	struct s_redir				*redir;
	struct s_env				*env;
	struct s_cmds				*cmds;
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

#endif
