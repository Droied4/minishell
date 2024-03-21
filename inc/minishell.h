/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/03/21 11:40:08 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../library/dprintf/ft_dprintf.h"
# include "../library/libft/libft.h"
# include "macros.h"
# include "struct.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include <editline/readline.h>

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

t_token	*generate_tokens(char *line);
int		ft_deltoken(t_token **lst);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	LEXER_AUX - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/

char	*add_between(char *s, char btween);
int		cont_meta(char *s);
void	token_type(t_token *lst);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	LEXER_AUX2 - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void	redifine_token(t_token *tok);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		PARSER - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void	parse_all(t_shell *sh);
int		parse_input(t_shell *sh);
void	parse_block(t_shell *sh);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	BLOCK_LST - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int		ft_del_blocks(t_block **lst);
t_block	*generate_blocks(t_token *tokens);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		PARSER BLOCK - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/
void	establish_block_type(t_shell *sh);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		PARSER CMD - 3
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

t_token	*fill_block(t_block **cmd, t_token *token);
t_token	*fill_cmd(t_block **cmd, t_token *token);
char	*add_space(char *info);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		PARSER INPUT - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int		syntax_error(t_token *tok);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		PARSER ENTRY - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int		input_unclosed(t_shell *sh);
void	unclosed_entry(t_shell *sh);
int		input_incomplete(t_shell *sh);
void	incomplete_entry(t_shell *sh);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
			AUX - 7
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int		ft_lstenv_size(t_env *lst);
int		ft_del_env(t_env **lst);
void	print_lst_env(t_env *lst, int i);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		AUX DEI - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/
void	print_tokens(t_token *lst);
void	print_blocks(t_block *lst);
char	*ft_imp_strjoin(char const *s1, char const *s2);
char	*char2str(char c);
void	ft_free_array(char **res);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	IS SOMETHING - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int		is_builtin(char *data);
int		is_charmeta(char c);
int		is_meta(int type);
int		is_redir(int type);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		ENV
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int		ft_del_env(t_env **lst);
t_env	*create_envnode(char *envp);
t_env	*create_lst_env(char **envp);
t_env	*exporting_var(t_shell sh, t_env **lst_env);
char	**convert_to_dchar(t_env *lst_env);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		BUILTINS
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void	execute_exit(t_shell *sh);
void	execute_export(t_shell *sh, char **env);
void	execute_builtins(t_shell *looking, char **env);

// void    display_env(env);
void	printlst(t_token *lst);
int		ft_del_env(t_env **lst);
void	print_lst_env(t_env *lst, int i);

/*
 *  ENV
 */
t_env	*create_envnode(char *envp);
t_env	*create_lst_env(char **envp);

t_env	*exporting_var(t_shell sh, t_env **lst_env);
char	**convert_to_dchar(t_env *lst_env);

/*
 *  BUILTINS
 */

void	init_shell(t_shell *sh);
void	execute_exit(t_shell *sh);
void	execute_export(t_shell *sh, char **env);
void	execute_builtins(t_shell *looking, char **env);

#endif
