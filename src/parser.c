/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/23 17:20:55 by deordone         ###   ########.fr       */
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
	char	*cosita;

	final_cmd = NULL;
	tmp_tok = token;
		// si voy a utilizar el valor de las tokens necesito duplicarlo
	if (tmp_tok->type == CMD)
	{
		cosita = ft_strdup(tmp_tok->data);
		new_cmd = ft_strjoin(cosita, "="); // para despues hacer un split
		free(cosita);
		tmp_tok = tmp_tok->next;
		if (tmp_tok && (tmp_tok->type == CMD || tmp_tok->type == FLAG
				|| tmp_tok->type == ARCH))	// avanzo y miro si el siguiente es un cmd flag o arch
		{
			cosita = ft_strdup(tmp_tok->data);
			new_cmd = ft_imp_strjoin(new_cmd, cosita); // si lo es lo concateno
		}
		final_cmd = ft_split(new_cmd, '='); // al final hago un split
		free(new_cmd);
		(*cmd)->cmd = final_cmd; // y guardo el comando en el cmd->cmd
	}
	return (tmp_tok);
}

/* version 3 del parse_cmd xD
void	parse_cmd(t_shell *sh)
{
	t_token *tmp_tok;
	t_cmds *tmp_cmd;
	
	tmp_cmd = sh->cmds;
	tmp_tok = sh->tokens;
	while (tmp_tok || tmp_cmd)
	{
	//	printf("indice -> %i\n", tmp_tok->index);
	//	tmp_tok = fill_cmd(tmp_cmd, tmp_tok);
		tmp_tok = tmp_tok->next;
	}
}
*/
void	parse_all(t_shell *sh)
{
	t_token *tmp_tok;

	tmp_tok = sh->tokens;
	//	parse_input(tokens); redifinir cosas y verificar cosas crear la copia del env
	total_pipes(sh, &sh->tokens);
	//parse_cmd(sh);🦊❗️
	fill_cmd(&sh->cmds, tmp_tok);
	print_tablecmd(sh->cmds);	
	// parse_expansor; supongo que toca parsearlo xd
}
