/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:03:11 by avolcy            #+#    #+#             */
/*   Updated: 2023/11/07 17:45:54 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>

char	*ft_strnstr(const char *b_str, const char *l_str, size_t len)
{
	size_t	i;
	size_t	j;

	if (*l_str == '\0')
		return ((char *)b_str);
	i = 0;
	j = 0;
	while (b_str[i] != '\0' && i < len && l_str[j])
	{
		j = 0;
		while (l_str[j] == b_str[i + j] && (i + j) < len
			&& l_str[j] && b_str[i + j])
		{
			++j;
		}
		if (!l_str[j])
			return ((char *)&(b_str[i]));
		++i;
	}
	return (0);
}
/*
int main()
{
	const char	bstr[19]="hola que tal bro";
	const char	lstr[]="bro";

	printf("test : %s\n", (char *)ft_strnstr(bstr, lstr, 19));
	printf("test : %s", (char *)strnstr(bstr, lstr, 19));
		return (0);
}*/
