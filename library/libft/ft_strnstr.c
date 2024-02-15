/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:24:55 by deordone          #+#    #+#             */
/*   Updated: 2023/11/09 13:30:33 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		i2;
	size_t		n_len;
	char		*rcver;

	i = 0;
	rcver = (char *)haystack;
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (rcver);
	while (rcver[i] != '\0' && i < len)
	{
		i2 = 0;
		while (rcver[i + i2] != '\0' && needle [i2] != '\0'
			&& rcver [i + i2] == needle [i2] && i + i2 < len)
			i2++;
		if (i2 == n_len)
			return (rcver + i);
		i++;
	}
	return (0);
}
