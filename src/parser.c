/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:02:55 by deordone          #+#    #+#             */
/*   Updated: 2024/02/21 11:25:17 by deordone         ###   ########.fr       */
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

void	parse_cmds(t_token *tokens)
{
	t_token tmp;
	int pipes;

	tmp = tokens;
	pipes = 0;
	while (tmp->next != NULL)
	{
		if(tmp->index == PIPE)
			++pipes;
	}
	printf("pipes ->%i", pipes);
}

void parse_all(t_token *tokens)
{
//	parse_input(tokens);//redifinir cosas y verificar cosas
	parse_cmds(tokens);//buscar la ruta de los comandos y prepararlos para el executor
	//parse_expansor; supongo que toca parsearlo xd
}
