/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:03:07 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 19:09:31 by avolcy           ###   ########.fr       */
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
