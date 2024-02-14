/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:32:42 by deordone          #+#    #+#             */
/*   Updated: 2023/09/20 17:46:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_trimstart(char const *s1, char const *set)
{
	size_t	l_s1;
	size_t	i;

	l_s1 = ft_strlen(s1);
	i = 0;
	while (i < l_s1)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_trimend(const char *s1, char const *set)
{
	size_t	l_s1;
	size_t	i;

	l_s1 = ft_strlen(s1);
	i = 0;
	while (i < l_s1)
	{
		if (ft_strchr(set, s1[l_s1 - i - 1]) == 0)
			break ;
		i++;
	}
	return (l_s1 - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*fstr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_trimstart(s1, set);
	end = ft_trimend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	fstr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (fstr == NULL)
		return (NULL);
	ft_strlcpy(fstr, s1 + start, end - start + 1);
	return (fstr);
}

/*
int main (void)
{
   char str[] = "lorem \n ipsum \t dolor \n sit \t amet";
   char to_find[] = " ";
   char *result2;

   result2 = ft_strtrim(str, to_find);
   printf("%s", result2);

   return (0);
}*/
