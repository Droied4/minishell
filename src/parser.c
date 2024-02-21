/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 12:18:13 by deordone         ###   ########.fr       */
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
		if(tmp->type == PIPE)
			++total_pipes;
		tmp = tmp->next;
	}
	sh->pipes = total_pipes;
}

void parse_all(t_shell *sh)
{
//	parse_input(tokens);//redifinir cosas y verificar cosas crear la copia del env
	total_pipes(sh, &sh->tokens);//buscar la ruta de los comandos y prepararlos para el executor
	//parse_expansor; supongo que toca parsearlo xd
}
