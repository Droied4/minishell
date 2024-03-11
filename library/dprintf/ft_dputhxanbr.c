/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhxanbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:31:09 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:03:00 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputhxanbr(int fd, unsigned int nb)
{
	char	*hex_val;
	int		count;

	count = 0;
	hex_val = "0123456789abcdef";
	if (nb > 15)
	{
		count = ft_dputhxanbr(fd, nb / 16);
		if (count == -1)
			return (-1);
	}
	if (ft_dputchar(fd, hex_val[nb % 16]) == -1)
		return (-1);
	count++;
	return (count);
}
