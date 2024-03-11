/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:11:48 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 19:09:27 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d_st;
	const char	*s_rc;

	d_st = (char *)dst;
	s_rc = (const char *)src;
	i = 0;
	if (!src && !dst)
		return (NULL);
	if (src < dst)
	{
		while (len--)
		{
			d_st[len] = s_rc[len];
		}
	}
	else
	{
		while (i < len)
		{
			d_st[i] = s_rc[i];
			i++;
		}
	}
	return (dst);
}
