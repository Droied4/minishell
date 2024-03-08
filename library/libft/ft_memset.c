/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:03:07 by avolcy            #+#    #+#             */
/*   Updated: 2023/05/22 16:30:55 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*nt;
	unsigned char	le;

	nt = b;
	le = c;
	i = 0;
	while (i < len)
	{
		nt[i] = le;
		++i;
	}
	return (b);
}
