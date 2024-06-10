/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:42 by avolcy            #+#    #+#             */
/*   Updated: 2024/06/02 20:57:07 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*aux_trim(char *data)
{
	int	pos_dquote;
	int	pos_squote;

	pos_dquote = char_is_inside(data, DQUOT);
	pos_squote = char_is_inside(data, SQUOT);
	if (pos_dquote < 0 && pos_squote >= 0)
		return (trimmer_quotes(data, SQUOT));
	else if (pos_squote < 0 && pos_dquote >= 0)
		return (trimmer_quotes(data, DQUOT));
	if (pos_dquote > 0 && pos_dquote > pos_squote)
		return (trimmer_quotes(data, SQUOT));
	else if (pos_squote > 0 && pos_squote > pos_dquote)
		return (trimmer_quotes(data, DQUOT));
	return (ft_strdup(""));
}

char	**split_env_var(char *str)
{
	int		i;
	int		len;
	int		position;
	char	**splitted;

	len = count_len(str);
	splitted = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		splitted[i] = find_env_part(str, &position);
		str = &str[position];
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	*find_env_part(char *str, int *pos)
{
	int		i;
	int		len;
	char	*part;

	len = count_len_env_part(str);
	*pos = len;
	part = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		part[i] = str[i];
		i++;
	}
	part[i] = '\0';
	return (part);
}

int	is_special_cases(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}
