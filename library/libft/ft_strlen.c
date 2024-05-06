/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:08:53 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/01 20:25:18 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *x)
{
	int	i;

	if (x == NULL || *x == '\0')
		return (0);
	i = 0;
	while (x[i] != '\0')
		++i;
	return (i);
}
/*int	main(void)
{
	char *v;

	v ="Imma Geek";
	printf("The lenght is :%d\n", ft_strlen(v));
	return (0);
}*/
