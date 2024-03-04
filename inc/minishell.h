/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/03/04 16:45:14 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../library/dprintf/ft_dprintf.h"
# include "../library/libft/libft.h"
# include "macros.h"
# include "struct.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include <editline/readline.h>
# include <readline/history.h>

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

t_token	*generate_tokens(char *line);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		PARSER - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void	parse_all(t_shell *sh);
void	parse_input(t_shell *sh);
void	parse_cmd(t_shell *sh);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	LST_TABLE_CMD - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

t_cmds	*generate_tablecmd(t_token *tokens);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		PARSER CMD - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void	total_pipes(t_shell *sh, t_token **tokens);
t_token *fill_cmd(t_cmds **cmd, t_token *token);
int		is_redir(int type);
char	*add_space(char *info);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
			AUX - 7
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int		is_meta(int type);
void	print_tokens(t_token *lst);
void	print_tablecmd(t_cmds *lst);
int		ft_deltoken(t_token **lst);
int		ft_delcmds(t_cmds **lst);
void	ft_free_array(char **res);
char	*ft_imp_strjoin(char const *s1, char const *s2);
/*
┏━━━━━━━━・▼・━━━━━━━━┓
		ENV
┗━━━━━━━━・▼・━━━━━━━━┛
*/

// void    display_env(env);

#endif
