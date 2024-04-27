/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:06:07 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/27 11:00:52 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_char(char *data, char c)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == c && data[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	number_of_quotes(char *s, char quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[i] == quotes)
			i++;
		j++;
	}
	return (i);
}

int	find_next_quote(char *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && c == '$')
			break ;
		else if (s[i] == c && c != '$')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	find_next_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != SQUOT && s[i] != DQUOT)
	{
		if (s[i] == SQUOT || s[i] == DQUOT)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*add_dollar_case(char *s, int i, int j)
{
	char	*new;

	new = my_allocation(ft_strlen(s) * 2);
	while (s[i] != '\0')
	{
		if (((s[i] == SQUOT && s[i + 1] && ft_isprint(s[i + 1]) \
			&& s[i + 1] != SQUOT)) || (s[i] != SQUOT && s[i + 1] \
				&& s[i + 1] == SQUOT))
		{
			new[j++] = s[i];
			new[j++] = '$';
		}
		else if ((s[i] == ' ' && s[i + 1] && ft_isprint(s[i + 1])) || (s[i + 1]
				&& ft_isprint(s[i]) && s[i + 1] == ' '))
		{
			new[j++] = s[i];
			new[j++] = '$';
		}
		else
			new[j++] = s[i];
		i++;
	}
	return (new[j++] = '\0', new);
}
