/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:55:41 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:03:05 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_isintmin(int fd, int count)
{
	if (write(fd, "-2", 2) == -1)
		return (-1);
	ft_dputstr(fd, "147483648");
	return (11 + count);
}

int	ft_dputnbr(int fd,int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		return (ft_isintmin(fd, count));
	if (nb < 0)
	{
		count += ft_dputchar(fd, '-');
		if (count == -1)
			return (-1);
		nb *= -1;
	}
	if (nb > 9)
	{
		count += ft_dputnbr(fd, nb / 10);
		if (count == -1)
			return (-1);
	}
	if (ft_dputchar(fd, (nb % 10) + '0') == -1)
		return (-1);
	count++;
	return (count);
}
