/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:50:03 by deordone          #+#    #+#             */
/*   Updated: 2024/01/21 13:42:26 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	howmdigits(int n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (i);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i - 1);
}

static char	*isnegative(char *str_num, int n, int digits)
{
	if (n < 0)
	{
		digits++;
		str_num = malloc(sizeof(char) * (digits + 1));
		if (!str_num)
			return (NULL);
		*str_num = '-';
	}
	else
		str_num = malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	str_num[digits] = '\0';
	return (str_num);
}

static char	*loop(char *str_num, int n, size_t digits, int nkeep)
{
	while (digits)
	{
		nkeep = nkeep / 10;
		n = n % 10 + '0';
		str_num[digits] = n;
		n = nkeep;
		digits--;
		if (n == 0)
			return (str_num);
	}
	return (str_num);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	size_t	digits;
	int		nkeep;

	str_num = "-2147483648";
	if (n == -2147483648)
		return (ft_strdup(str_num));
	digits = howmdigits(n);
	str_num = isnegative(str_num, n, digits);
	if (!str_num)
		return (NULL);
	if (n >= 0)
		digits--;
	else
		n = n * -1;
	nkeep = n;
	return (loop(str_num, n, digits, nkeep));
}
