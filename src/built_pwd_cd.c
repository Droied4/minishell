/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:13:30 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/19 20:44:15 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", s);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	execute_cd(t_shell *sh)
{
}