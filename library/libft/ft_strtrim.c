/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:00:22 by avolcy            #+#    #+#             */
/*   Updated: 2023/06/11 19:30:25 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	len;
	size_t	i;

	res = 0;
	if (!set)
		return (ft_strdup(s1));
	if (s1 && set)
	{
		i = 0;
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		len = ft_strlen(s1);
		if (len <= i)
			return (ft_strdup(""));
		while (s1[len - 1] && ft_strchr(set, s1[len - 1]) && len > i)
			len--;
		res = malloc((len - i + 1) * sizeof(char));
		if (!res)
			return (NULL);
		ft_strlcpy(res, &s1[i], len - i + 1);
	}
	return (res);
}
