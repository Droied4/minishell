/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:56 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/13 19:56:55 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' && str[1])
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	execute_echo(t_shell *sh)
{
	int		i;
	int		flags;
	char	**matrix;

	i = 1;
	flags = 0;
	matrix = sh->pro.w->cmd;
	while (is_flag(matrix[i]))
	{
		flags++;
		i++;
	}
	while (matrix[i])
	{
		if (matrix[i + 1])
			printf("%s ", matrix[i]);
		else
			printf("%s", matrix[i]);
		i++;
	}
	if (!flags)
		printf("\n");
}

int	found_equal(char *line, char ch)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == ch)
			return (1);
		i++;
	}
	return (0);
}
