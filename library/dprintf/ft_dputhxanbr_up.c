/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhxanbr_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:15:20 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:02:57 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputhxanbr_up(int fd, unsigned int nb)
{
	char	*hex_val;
	int		count;

	count = 0;
	hex_val = "0123456789ABCDEF";
	if (nb > 15)
	{
		count = ft_dputhxanbr_up(fd, nb / 16);
		if (count == -1)
			return (-1);
	}
	if (ft_dputchar(fd, hex_val[nb % 16]) == -1)
		return (-1);
	count++;
	return (count);
}
