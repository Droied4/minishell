/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:10:37 by avolcy            #+#    #+#             */
/*   Updated: 2023/05/30 16:53:57 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while ((i < dstsize - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*int main()
{
	const	char *src ="Ahora lo entiendo bien tio !";
	char	dst[15];
	
	printf("Fake function :%zu", ft_strlcpy(dst, src, sizeof(dst)));
	printf("\nDestination = %s", dst);
	printf("\nOriginal function :%lu", strlcpy(dst, src, sizeof(dst)));
	printf("\nDestination = %s", dst);
	return (0);	
}*/
