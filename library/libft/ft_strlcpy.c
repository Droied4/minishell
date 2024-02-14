/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:37:57 by deordone          #+#    #+#             */
/*   Updated: 2023/11/09 13:10:19 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = -1;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[++count] != '\0' && count < (dstsize - 1))
		dst[count] = src[count];
	dst[count] = '\0';
	return (ft_strlen(src));
}
