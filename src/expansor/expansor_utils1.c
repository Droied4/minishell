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


int is_special_cases(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

int dol_count_words(char *str, int i, int count, int in_word)
{
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '$' && str[i + 1] == '?')
        {
            count++;
            i += 2;
        }
        else if (str[i])
        {
            in_word = 1;
            while (str[i] && !(str[i] == '$' && str[i + 1] == '?') && \
				str[i] != ' ' && str[i] != '\t')
                i++;
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
    }
    return count;
}

int len_part(char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
        {
            if (len == 0)
                len = 2;
            break;
        }
        len++;
        i++;
    }
    return (len);
}

char *small_part(char *str, int *pos)
{
	int i;
	int len;
	char *part;

	len = len_part(str);
	*pos = len;
	part = malloc(sizeof(char) * len + 1);
	if (!part)
		return (NULL);
	i = -1;
	while (++i < len)
		part[i] = str[i];
	part[i] = '\0';
	return (part);
}

char	**split_dollar_interog(char *str)
{
	int i;
	int pos;
	char **result;
	int num_dol_int;

	num_dol_int = dol_count_words(str, 0, 0, 0);
	result = malloc(sizeof(char *) * num_dol_int + 1);
	if (!result)
		return (NULL);
	i = -1;
	pos = 0;
	while (++i < num_dol_int)
	{
		result[i] = small_part(str, &pos);
		str += pos;
	}
	result[i] = NULL;
	return (result);
}

char	*special_cases(char *special, int exit_status)
{
	int i;
	char  *str_exit;
	char **split_exit;

	i = 0;
	if (g_signals != 0)
	{
		exit_status = g_signals;
		g_signals = 0;
	}
	str_exit = ft_itoa(exit_status);
	split_exit = split_dollar_interog(special);
	if (!split_exit)
    return (NULL);
	while (split_exit[i])
	{
		if (!ft_strncmp("$?", split_exit[i], 3))
			split_exit[i] = ft_strdup(str_exit);
		i++;
	}
	free(str_exit);
	str_exit = join_split(split_exit);
	free_matrix(split_exit);
	return (str_exit);
}
