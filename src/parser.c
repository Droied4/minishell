/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/28 20:07:06 by deordone         ###   ########.fr       */
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

static char	*add_space(char *info)
{
	char *s;
	char *new_s;
	
	if (info)
	{
		s = ft_strdup(info);
		new_s = ft_strjoin(s, " ");
		free(s);
		return (new_s);
	}
	else
		return (NULL);
}

t_token	*fill_cmd(t_cmds **cmd, t_token *token)
{
	t_token	*tmp_tok;
	char	*new_cmd;
	char	**final_cmd;
	char	*flag;

	final_cmd = NULL;
	tmp_tok = token;
	if (!tmp_tok)
		return NULL;
	new_cmd = tmp_tok->data;	
	new_cmd = add_space(new_cmd);
		// si voy a utilizar el valor de las tokens necesito duplicarlo
	while (tmp_tok && tmp_tok->type != PIPE)
	{
		tmp_tok = tmp_tok->next;
		if (tmp_tok && (tmp_tok->type == CMD || tmp_tok->type == FLAG
			|| tmp_tok->type == ARCH))	// avanzo y miro si el siguiente es un cmd flag o arch
		{
			flag = add_space(tmp_tok->data);
			new_cmd = ft_imp_strjoin(new_cmd, flag); // si lo es lo concateno
		}
		else
			final_cmd = ft_split(new_cmd, ' '); // al final hago un split
	}
	free(new_cmd);
	if (final_cmd == NULL)
		return (tmp_tok->next);
	else
		(*cmd)->cmd = final_cmd; // y guardo el comando en el cmd->cmd
	return (tmp_tok);
}

/* version 3 del parse_cmd xD*/
void	parse_cmd(t_shell *sh)
{
	t_token *tmp_tok;
	t_cmds *tmp_cmd;

	tmp_cmd = sh->cmds;
	tmp_tok = sh->tokens;
	while (tmp_tok != NULL || tmp_cmd != NULL)
	{
		tmp_tok = fill_cmd(&tmp_cmd, tmp_tok);
		if (tmp_cmd)
			tmp_cmd = tmp_cmd->next; 
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
