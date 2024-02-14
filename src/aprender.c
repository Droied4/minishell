/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aprender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmeno <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:56:19 by carmeno           #+#    #+#             */
/*   Updated: 2024/02/11 16:27:44 by carmeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

PARSER
	INPUT
		[hola_como < cat hola ls -la > adios]

	LEXICAL ANALYZER
		[WORD][WORD][LRD][CMD][PIPE][CMD][FLAG][RRD][WORD] 
		[hola_como ][ < ][cat][  | ][ls ][-la ][ > ][file]

	TABLE OF COMANDS
		[cat][input: fd(hola_como)][output: PIPE]
		[ls -la][input: PIPE][output: fd(file)]
EXECUTOR
	INTERPRETA SI ES UN CMD o UNA PALABRA RESERVADA O UNA FLAG O LO QUE SEA Y ACTUA EN CONSECUENCIA
/*
//ejemplo de como usar getenv 
int main (int argc, char **argv)
{
	char *rslt;
	if (argc == 2)
	{
		rslt = getenv(argv[1]);
		if (rslt)
			printf("%s", rslt);
		else
			printf("variable de entorno incorrecta o no definida");
	}
	return (0);
}*/
/*
//ejemplo de como usar unlink para borrar archivos
int main (void)
{
		if (unlink("/home/carmeno/Workspace/42-cursus/weekend/minishell/prueba/borrar/hola") == 0)
			printf("se borro");
		else
			printf("no se borro");	
	return (0);
}
*/
/*
//ejemplo de como usar getcwd perror strerror y errno
int main (int argc, char **argv)
{
	char *rslt = NULL;
	if (argc == 2)
	{
		rslt = getcwd(rslt, 58);
		if (rslt)
		{
			printf("%s",rslt);
			free(rslt);
		}
		else
		{
			printf ("%s ", argv[1]);
			perror("zsh ");
			//printf ("%s", strerror(errno));
		}
	}	
	return (0);
}*/
/*
//ejemplo de como entrar en un directorio y hacer cositas
int main (int argc, char **argv)
{
	int i = 1;
	if (argc == 2)
	{
		if (chdir(argv[i]) == 0)
		{
			printf("perfect");
			open("file.txt", O_CREAT);
		}
		else
			printf("no existe el directorio");
	}	
	return (0);
}
*/

