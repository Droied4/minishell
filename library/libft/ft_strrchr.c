/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:36:31 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 19:09:52 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int i)
{
	char	*l_st;

	l_st = NULL;
	while (*str != '\0')
	{
		if (*str == (char)i)
			(l_st = (char *)str);
		++str;
	}
	if (((char)*str) == (char)i)
		(l_st = (char *)str);
	return (l_st);
}
