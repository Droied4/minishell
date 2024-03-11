/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:55:37 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:03:10 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputstr(int fd, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_dputstr(fd, "(null)"));
	while (str[i])
	{
		if (write(fd, &str[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}
