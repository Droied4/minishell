/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:45:27 by deordone          #+#    #+#             */
/*   Updated: 2023/10/04 12:32:52 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size * count);
	if (!str)
		return (NULL);
	while (i < (int)(size * count))
	{
		str[i] = '\0';
		i++;
	}
	return ((void *)str);
}
