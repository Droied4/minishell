/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:28:30 by avolcy            #+#    #+#             */
/*   Updated: 2023/10/18 19:00:51 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cnt_word(const char *s, char c)
{
	int		i;
	int		word;
	int		count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count = 0;
		else if (count == 0)
		{
			count = 1;
			word++;
		}
		i++;
	}
	return (word);
}

void	ft_free_array(char **res, int i)
{
	while (i--)
	{
		free(res[i]);
	}
	free(res);
}

char	**ft_create(char const *s, char c, char **res)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			res[j] = ft_substr(s, start, i - start + 1);
			if (!res[j])
			{
				ft_free_array(res, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = malloc(sizeof(char *) * (ft_cnt_word(s, c) + 1));
	if (!result)
		return (NULL);
	result = ft_create(s, c, result);
	return (result);
}
/*
int main ()
{
	char **test;
	int i = 0;

	test = ft_split("   bonjou,   koman  nou ye   ", ' ');
	while (test[i])
	{
		printf("the column%d is -> |%s|\n", i, test[i]);
		i++;
	}
	return (0);
}*/
