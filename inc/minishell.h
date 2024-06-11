/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/05/31 17:02:19 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../library/dprintf/ft_dprintf.h"
# include "../library/libft/libft.h"
# include "../library/readline/history.h"
# include "../library/readline/readline.h"
# include "macros.h"
# include "struct.h"
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

extern volatile sig_atomic_t	g_signals;

void							restore_terminal_settings(void);
void							disable_control_chars_echo(void);
void							ft_signals(t_shell *sh, t_signal mode);

int								ft_deltoken(t_token **lst);
t_token							*generate_tokens(char *line);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	NEW_LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								len_matriz(char *line);
int								lex_word_case(char *s);
int								lex_redir_case(char *s, char redir);
int								lex_quotes_case(char *s, char quote);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	LEXER_AUX - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								cont_meta(char *s);
void							token_type(t_token *lst);
char							**montage_tokens(char *line);
char							*add_between(char *s, char btween);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
  LEXER_AUX2 - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void							redifine_token(t_token *tok);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
  PARSER - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int								parse_all(t_shell *sh);
void							parse_words(t_shell *sh);
void							find_path(t_words *word);
int								parse_input(t_shell *sh);
int								parse_redirections(t_shell *sh);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	WORD_LST - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								ft_del_words(t_words **lst);
t_words							*generate_words(t_token *tokens);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	REDIR_LST - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								ft_del_redirs(t_redir **lst);
t_redir							*generate_redirs(t_token *tokens);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		EXPANSOR - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void							expansor(t_shell *sh);
char							**split_quotes(char *str);
char							*expand_data(t_shell *sh, char *str);
char							*expand_string(t_shell *sh, char *str);
char							*expansion_final(t_shell *sh, char *str);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 1 - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

char							*aux_trim(char *data);
char							**split_env_var(char *str);
char							*find_env_part(char *str, int *pos);
char							*special_cases(char *special, int exit_status);
char							*is_special_dollar(char *data, int num_dollar,
									int i);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 2 - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int								count_len(char *str);
int								get_len_string(char *str);
int								count_len_env_part(char *str);
int								is_special_cases(char *sp_case);
int								count_words(char *str, int count, int is_sq,
									int is_dq);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 3 - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/
char							*join_split(char **split);
int								found_char(char *data, char c);
char							*ft_get_cpy(char *str, int *pos);
char							*trimmer_quotes(char *str, int quotes);
int								number_of_char(char *str, char charact);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 4 - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int								len_part(char *str);
char							*small_part(char *str, int *pos);
char							*special_cases(char *special, int exit_status);
int								dol_count_words(char *str, int i, int count,
									int in_word);
/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
   PARSER BLOCK - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void							montage_redirections(t_token *tok,
									t_redir *redir);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
	PARSER CMD - 3
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

char							*add_space(char *info);
t_token							*fill_cmd(t_words **cmd, t_token *token);
t_token							*fill_block(t_words **cmd, t_token *token);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
   PARSER INPUT - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int								syntax_error(t_token *tok);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
	PARSER ENTRY - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int								input_unclosed(t_shell *sh);
void							unclosed_entry(t_shell *sh);
int								input_incomplete(t_shell *sh);
void							incomplete_entry(t_shell *sh);
/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		MANAGE  - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void							soft_exit(t_shell *sh);
void							hard_exit(t_shell *sh);
int								after_exec(t_words *word);
void							ft_free_array(char **res);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
		EXECUTOR - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void							executor(t_shell *sh);
char							*prompt(int exit_status);
// void execute_cmd(t_block *block);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
	EXEC REDIR  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void							process_redir(t_shell *sh, t_process *pro);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
  EXEC CMDS  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

char							*ft_check_path(char **paths, char **cmd);
int								process_word(t_shell *sh, int wstatus,
									int exit_status);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
 EXEC CONEC  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int								manage_signals(t_shell *sh, t_signal mode);
int								process_connector(t_shell *sh, int process);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	AUX ARCH- 7
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								ft_del_env(t_env **lst);
int								ft_lstenv_size(t_env *lst);
int								is_correct_name(char *name);
void							print_lst_env(t_env *lst, int i);
t_token							*quotes_removal(t_token *tokens);
char							*quotes_removal_master(char *cmd_line);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
	AUX DEI - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/
char							*char2str(char c);
void							print_words(t_words *lst);
void							print_redir(t_redir *lst);
void							print_tokens(t_token *lst);
int								stock_of(t_shell *sh, int type);
char							**get_envivar(char *var, char **env);
int								char_is_inside(const char *str, char c);
char							*ft_imp_strjoin(char const *s1, char const *s2);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
  IS SOMETHING - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								is_meta(int type);
int								is_redir(int type);
int								is_charmeta(char c);
int								is_char_redir(char c);
int								is_builtin(char *data);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
				ENV
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								ft_del_env(t_env **lst);
t_env							*create_envnode(char *envp);
t_env							*create_lst_env(char **envp);
char							**convert_env_dchar(t_env *lst_env, char **env);
t_env							*exporting_var(t_shell sh, t_env **lst_env,
									t_env *new);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
		BUILTINS
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int								execute_pwd(void);
void							free_matrix(char **sh);
void							printlst(t_token *lst);
int								ft_del_env(t_env **lst);
int								execute_exit(t_shell *sh);
int								token_size(t_token *tokens);
void							execute_echo(t_shell *shell);
int								check_exp_variable(t_env *tok);
void							print_lst_env(t_env *lst, int i);
t_env							*found_var(char *var, t_env *lst);
void							execute_env(t_shell *sh, char **env);
void							execute_export(t_shell *sh, char **env);
int								execute_builtins(t_shell *looking, char **env);
int								execute_cd(t_shell *sh, char *path, char **env);
void							execute_unset(t_shell **sh, t_env *node,
									char **env);

#endif
