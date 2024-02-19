/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:15:32 by deordone          #+#    #+#             */
/*   Updated: 2024/02/17 20:03:00 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//vale tienes que hacer muchas cosas
//pero sobre todo hacer algo organizado entonces empecemos

t_token *less_case(t_token *temp, t_analyzer *block)
{
	if (!temp->next)
	       BUG;//personalizar fallo si solo pasamos < y no hay nada despues
	if (temp->next->type != ARG)
		BUG;//fallo de strerror
	temp = temp->next;
	block->input = open(temp->data, O_RDONLY);
	if (block->input < 0)
		BUG; //fallo de strerror
	temp = temp->next;
	return (temp);
}
//para que entiendas lo que esta pasando por mi cabeza, en teoria tiene que ser una funcion recursiva que me vaya almacenando x cantidadd de estructuras analyzed
//luego esas estructuras las pasare a mi executor pero aqui tengo que ver que todo este bien hecho
t_analyzer	*block_parser(t_token *token)
{
	t_analyzer block;
	t_token temp;

	temp = token;
	while (temp)
	{
		if (token->type == LESS)
			temp = less_case(temp, &block);
	//	SI ME PASAN ">"  ENTONCES CREO UN ARCHIVO DEL SIGUIENTE ARGUMENTO SOLAMENTE SI ES DE TIPO ARG
	//		great_case(token, &block);
	//	SI ME PASAN "PIPE" ENTONCES QUE EL ARCHIVO SIGUIENTE SEA UN ARG
	//		pipe_case(token, &block);
	//	SI ME PASAN "ARG" ENTONCES QUE MIRE EL SIGUIENTE Y SI TIENE "-" o "--" QUE LO GUARDE EN **cmd
	}
}

//en el token parser debo separar por bloques de ejecucion, y el final de estos bloques de ejecucion sera un GREAT
//entonces debo recorrer la lista hasta encontrar un > y en el momento en el que lo encuentre crear la estructura con la tabla de ejecucion
//cuando tenga esta parte segmentada debo tambien verificar si todo lo que me han pasado es correcto.

void	token_parser(t_token *token)
{
	t_token *temp;

	temp = token;
	while ((temp != GREAT && temp)
		temp = temp->next;
	if (temp)
		printf("index -> %i", ++temp->index);
	  1			2	3	4	5	6	7
	[ < ]			[ in ]	[ hola ][ | ]	[ adios ][ > ]	[ out ]
	block_parser(t_token *token);
}
