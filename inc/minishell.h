/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/03/01 15:45:35 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../library/libft/libft.h"
# include "../library/dprintf/ft_dprintf.h"
# include "macros.h"
# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
//# include <editline/readline.h>
# include <readline/history.h>

/*
 * LEXER
 */

t_token	*generate_tokens(char *line);

/*
 *AUX PARSER
 */

char **build_cmd(t_token *tmp_tok, char *new_cmd);
char	*add_space(char *info);

/*
 * PARSER
 */

void	total_pipes(t_shell *sh, t_token **tokens);
void	parse_all(t_shell *sh);
void	parse_cmd(t_shell *sh);
t_token	*fill_cmd(t_cmds **cmd, t_token *token);

/*
 * AUX
 */

void	print_tokens(t_token *lst);
void	print_tablecmd(t_cmds *lst);
int		ft_deltoken(t_token **lst);
int		ft_delcmds(t_cmds **lst);
void	ft_free_array(char **res);
char *ft_imp_strjoin(char const *s1, char const *s2);

/*
 * LST PARSER
 */

t_cmds *generate_tablecmd(t_token *tokens);

/*
 *  ENV
 */
//void    display_env(env);

#endif
