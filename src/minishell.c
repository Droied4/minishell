/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:59 by deordone          #+#    #+#             */
/*   Updated: 2024/02/15 16:58:08 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av)
{
		char *line;

	if (ac == 1)
	{
		ft_dprintf(2, "hola\n%s\n", av[0]);
		// Mostrar el prompt al usuario y leer la línea de entrada
		line = readline("Ingresa una línea de texto: ");
		// Imprimir la línea de entrada
		printf("La línea ingresada es: %s\n", line);
		// Liberar la memoria asignada para la línea de entrada
		free(line);
	}
	return (0);
}
