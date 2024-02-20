/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/02/20 20:01:20 by deordone         ###   ########.fr       */
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
 * LST
 */

void	printlst(t_token *lst);

t_token	*generate_tokens(char *line);
void	create_lst(t_token **lst, t_token *new);
t_token	*add_to_end(t_token *lst);
t_token	*create_node(char *content);

#endif
