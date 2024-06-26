/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhxaptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 01:03:55 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:03:03 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputhxaptr(int fd, unsigned long nb)
{
	char	*pointer_val;
	int		count;

	count = 0;
	pointer_val = "0123456789abcdef";
	if (!nb)
		return (ft_dputchar(fd, '0'));
	if (nb > 15)
	{
		count = ft_dputhxaptr(fd, nb / 16);
		if (count == -1)
			return (-1);
	}
	if (ft_dputchar(fd, pointer_val[nb % 16]) == -1)
		return (-1);
	count++;
	return (count);
}
