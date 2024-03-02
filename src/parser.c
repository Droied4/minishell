/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/02 16:45:07 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	parse_input(t_token *tokens)
{

	//redifinir los tipos
	//comprobar que los tipos esten bien
	//es decir que antes de flag haya un comando que delante de pipe y
	//delante de < or > no haya otra redireccion
}*/
void	total_pipes(t_shell *sh, t_token **tokens)
{
	t_token	*tmp;
	int		total_pipes;

	tmp = *tokens;
	total_pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			++total_pipes;
		tmp = tmp->next;
	}
	sh->pipes = total_pipes;
}

t_token	*fill_cmd(t_cmds **cmd, t_token *token)
{
	t_token	*tmp_tok;
	char	*new_cmd;
	char	**final_cmd;

	tmp_tok = token;
	if (!tmp_tok)
		return NULL;
	new_cmd = tmp_tok->data;
	new_cmd = add_space(new_cmd);
	final_cmd = build_cmd(tmp_tok, new_cmd); // al final hago un split
	while (tmp_tok && is_redir(tmp_tok->type) == -1)
		tmp_tok = tmp_tok->next;
	if (final_cmd == NULL)
		return (tmp_tok->next);
	else
		(*cmd)->cmd = final_cmd; // y guardo el comando en el cmd->cmd
	return (tmp_tok);
}

void	parse_cmd(t_shell *sh)
{
	t_token *tmp_tok;
	t_cmds *tmp_cmd;

	tmp_cmd = sh->cmds;
	tmp_tok = sh->tokens;
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
	/*t_token *tmp_tok;

	tmp_tok = sh->tokens;
	//	parse_input(tokens); redifinir cosas y verificar cosas crear la copia del env*/
	total_pipes(sh, &sh->tokens);
	parse_cmd(sh);//🦊❗️
	print_tablecmd(sh->cmds);	
//	fill_cmd(&sh->cmds, tmp_tok);
	// parse_expansor; supongo que toca parsearlo xd
}
