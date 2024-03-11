/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputunsnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:31:42 by deordone          #+#    #+#             */
/*   Updated: 2024/03/11 19:03:08 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputunsnbr(int fd, unsigned int nb)
{
	int	count;

	count = 0;
	if (nb > 9)
	{
		count += ft_dputunsnbr(fd, nb / 10);
		if (count == -1)
			return (-1);
	}
	if (ft_dputchar(fd, (nb % 10) + '0') == -1)
		return (-1);
	count++;
	return (count);
}
