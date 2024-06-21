/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:13:33 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/30 20:33:59 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trimmer_quotes(char *str, int quotes)
{
	int		i;
	int		j;
	size_t	len;
	char	*trimmed;
	int		num_quotes;

	len = ft_strlen(str);
	num_quotes = number_of_char(str, quotes);
	trimmed = malloc(sizeof(char) * (len - num_quotes) + 1);
	if (!trimmed)
		exit(1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != quotes)
			trimmed[j++] = str[i];
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

int	number_of_char(char *str, char charact)
{
	int	len;

	len = 0;
	while (str && *str)
	{
		if (*str == charact)
			len++;
		str++;
	}
	return (len);
}

int	found_char(char *data, char c)
{
	int	i;

	i = 0;
	if (!data)
		return (0);
	while (data[i])
	{
		if (data[i] == c && data[i + 1])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_cpy(char *str, int *pos)
{
	int		i;
	int		len;
	char	*cpy;

	len = get_len_string(str);
	*pos = len;
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[len] = '\0';
	return (cpy);
}

char	*join_split(char **split)
{
	int		i;
	char	*tmp;
	char	*join;

	i = 0;
	join = NULL;
	while (split[i])
	{
		tmp = ft_strjoin2(&join, split[i]);
		if (!tmp)
			return (free(join), NULL);
		join = tmp;
		i++;
	}
	return (join);
}
