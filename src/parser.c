/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 16:42:51 by deordone         ###   ########.fr       */
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

void	total_pipes(t_shell *sh , t_token **tokens)
{
	t_token *tmp;
	int total_pipes;

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
/* el parse cmd esta muy desordenado cuando vuelva lo arreglo
t_cmds	*parse_cmd(t_shell *sh)
{
	t_cmds *cmd;
	t_token *tmp;
	t_token *tmp2;

	tmp = sh->tokens;
	tmp2 = sh->tokens;
	while (tmp)	
	{	
		if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	while (tmp2 == tmp)
	{
		if (temp2->type == LESS)
		{
			tmp2 = tmp2->next;
			cmd->in_file = temp2->data;
		}
		else if (temp2->type == CMD)
		{
			if (temp2->next->type == FLAG || temp2->next->type == CMD)
				//hacer un char ** con el cmd y el cmd o el cmd y el flag
			else 
//				hacer un char ** pero solo con el cmd
		}
		else if (temp2->type == GREAT)
		{
			tmp2 = tmp2->next;
			cmd->out_file = temp2->data;
		}
		else if (temp2->type == PIPE)
		{
			//esto es lo mas complicado buscate la vida deivid del futuro
		}
		tmp2 = tmp2->next;
	}
}
*/
void parse_all(t_shell *sh)
{
	
//	parse_input(tokens);//redifinir cosas y verificar cosas crear la copia del env
	total_pipes(sh, &sh->tokens);//buscar la ruta de los comandos y prepararlos para el executor
//	sh.cmds = parse_cmd(sh);
	//parse_expansor; supongo que toca parsearlo xd
}
