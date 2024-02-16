/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:39:02 by avolcy            #+#    #+#             */
/*   Updated: 2023/06/12 20:27:56 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convers(char *s, long n, long len)
{
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--len] = (n % 10) + 48;
		n = n / 10;
	}
	return (s);
}

static long	ft_d_cnt(long num)
{
	int		len;

	len = 0;
	if (num <= 0)
		len = 1;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = ft_d_cnt(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	res = ft_convers(res, n, len);
	return (res);
}
