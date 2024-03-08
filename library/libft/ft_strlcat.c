/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:35:12 by avolcy            #+#    #+#             */
/*   Updated: 2023/05/30 16:25:32 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_ln;
	size_t	d_ln;

	s_ln = ft_strlen(src);
	d_ln = ft_strlen(dst);
	if (d_ln > dstsize || !dstsize)
		return (dstsize + s_ln);
	i = 0;
	while (src[i] != '\0' && d_ln + i < dstsize - 1)
	{
		dst[d_ln + i] = src[i];
		++i;
	}
	dst[d_ln + i] = '\0';
	return (s_ln + d_ln);
}
