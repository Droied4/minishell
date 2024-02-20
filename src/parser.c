/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:15:32 by deordone          #+#    #+#             */
/*   Updated: 2024/02/20 16:57:01 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
//vale tienes que hacer muchas cosas
//pero sobre todo hacer algo organizado entonces empecemos

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

void	token_parser(t_token **token)
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
}*/

int	redir_cases(t_token *token)
{
	if (token->type == PIPE)//modificar error prev
	{
		if (!token->prev)
			BUG; //return 1
	}
	if (!token->next)
		BUG; //return 1
	else if (token->type == LESS || token->type == DLESS || token->type == GREAT || token->type == DGREAT)
	{
		if (token->next->type != ARCH)
	    	 BUG;//personalizar fallo si solo pasamos < y no hay nada despues y retornar 1 //fallo de strerror retornar 1
	}
	return (0);
}

int	prev_cases(t_token *token)
{
	if (token->type == FLAG)
	{
		if (token->prev->type != CMD)
			BUG; //return 1
	}
	else if (token->type == ARCH)
	{
		if (token->prev->type != LESS || token->prev->type != DLESS || token->prev->type != GREAT || token->prev->type != DGREAT)
			BUG; //return 1
	}
	return (0);
}

int	(*token_case(int type)(t_token *))
{
	if (type == LESS || type == GREAT || type == DLESS || type == DGREAT || type == PIPE)
		return redir_cases;
	else if (type == FLAG || type == ARCH)
		return prev_cases;
	else if (type == SQUOTE)
		return squote_case;
	else if (type == DQUOTE)
		return dquote_case;
	else 
		return NULL;
// solo faltan dos casos CMD y EXP
}
//mensaje para el deivid del futuro
//haz hecho una funcion que regresa un puntero
//a otras funciones 
//basicamente dependiendo del caso haras una funcion
//que compruebe una cosa u otra
void	check_token(t_token **token)
{
	t_token *temp;
	int	perfect;
	int	(*assign_case)(t_token *token); //declaracion del puntero a funcion

	perfect = 0;
	temp = *token;
	while(temp)
	{
		assign_case = token_case(token->type);
		if (assign_case) // si se ha asignado una funcion valida
			perfect += assign_case(*token); //ejecuto la funcion y guardo su valor de estado en perfect el cual al final debe ser 0
		temp = temp->next; //avanzo al siguiente nodo y repito
	}
}

void	token_parser(t_token **token)
{
	check_token(token);
}
