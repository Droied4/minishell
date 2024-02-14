/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:37:39 by deordone          #+#    #+#             */
/*   Updated: 2023/11/09 13:05:02 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *str, int c, size_t len)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (i < (int) len)
		s[i++] = c;
	return ((char *)str);
}
/*
int	main(void)
{
	char str3[] = "hola";

	ft_memset(str3, 'a', 2);
	return (0);
}*/
