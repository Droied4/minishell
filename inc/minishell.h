/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/02/22 20:22:51 by avolcy           ###   ########.fr       */
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
# include <editline/readline.h>
# include <readline/history.h>

/*
 * LEXER
 */

t_token	*create_node(char *content);
t_token	*add_to_end(t_token *lst);
void	create_lst(t_token **lst, t_token *new);
void	token_type(t_token *lst);
t_token	*generate_tokens(char *line);

/*
 * PARSER
 */

void	total_pipes(t_shell *sh, t_token **tokens);
void	parse_all(t_shell *sh);

/*
 * AUX
 */
int		ft_del(t_token **lst);
void	printlst(t_token *lst);
int     ft_del_env(t_env **lst);
void    print_lst_env(t_env *lst);

/*
 *  ENV
 */
int	ft_del_env(t_env **lst);
int display_env(t_token *tokens, char **argv, char **envp);

#endif
