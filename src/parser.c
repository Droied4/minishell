/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/12 22:43:34 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void   incomplete_entry(t_shell *sh)
{
        char *new_input;
        char *last_input;

        new_input = readline(GREEN"\n> "NC);
        last_input = add_space(new_input);
        free(new_input);
        sh->line = ft_imp_strjoin(sh->line, last_input);
        ft_deltoken(&sh->tokens);
        sh->tokens = generate_tokens(sh->line);
}


static int input_incomplete(t_shell *sh)
{
	t_token *tmp_tok;

	tmp_tok = sh->tokens;
	while (tmp_tok)
	{
		if (tmp_tok->type == PIPE && !tmp_tok->next)
			return (-1);
		tmp_tok = tmp_tok->next;
	}
	return (0);
}

int	parse_input(t_shell *sh)
{
	t_token *tmp_tok;
	int flag;

	tmp_tok = sh->tokens;
	flag = 0;
	if (syntax_error(tmp_tok) < 0)
		return (-1);
	while (input_unclosed(sh) < 0 && ++flag)
		unclosed_entry(sh);
	while (input_incomplete(sh) < 0 && ++flag)
	{
		incomplete_entry(sh);
		tmp_tok = sh->tokens;
		if (syntax_error(tmp_tok) < 0)
			return (-1);
	}
	if (flag > 2)
	{
		if (parse_input(sh) < 0)
			return(-1);
	}
	return (0);
}

void	parse_cmd(t_shell *sh)
{
	t_token *tmp_tok;
	t_cmds *tmp_cmd;

	tmp_cmd = sh->cmds;
	tmp_tok = sh->tokens;
	total_pipes(sh, &sh->tokens);
	while (tmp_tok != NULL || tmp_cmd != NULL)
	{
		if (tmp_cmd)
		{
			tmp_tok = fill_cmd(&tmp_cmd, tmp_tok);
			tmp_cmd = tmp_cmd->next; 
		}
		else
			break ;
	}
}

void	parse_all(t_shell *sh)
{
	if (parse_input(sh) < 0)
	   return ;
	// parse_expansor; supongo que toca parsearlo xd
	sh->cmds = generate_tablecmd(sh->tokens);
	parse_cmd(sh);
	//print_tablecmd(sh->cmds);
}
