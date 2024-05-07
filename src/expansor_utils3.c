/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:13:33 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/07 19:26:10 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char    *ft_get_cpy(char *str, int *pos)
{
    char    *cpy;
    int     len;
    int     i;

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
    cpy[i] = '\0';
    return (cpy);
}

char    *join_split(char **split)
{
    char    *join;
    char    *tmp;
    int     i;

    i = 0;
    join = NULL;
    while (split[i])
    {
        tmp = ft_strjoin2(join, split[i]);
        if (!tmp)
            return (free(join), NULL);
        join = tmp;
        i++;
    }
    return (join);
}
char    *trimmer_quotes(char *str, int quotes)
{
    if (quotes == SQUOT)
        return(ft_strtrim(str, "\'"));
    return(ft_strtrim(str, "\""));

}

int number_of_quotes(char *str, char quotes)
 {
     int len;

     len = 0;
     while (str && *str)
     {
         if (*str == quotes)
             len++;
         str++;
     }
     return (len);
 }
// char    *trimmer_quotes(char *str, int quotes)
// {
//     int i;
//     int len;
//     char *new_str;

//     i = 0;
//     len = ft_strlen(str) - number_of_quotes(str, quotes);
//     new_str = malloc(sizeof(char) * (len + 1));
//     if (!new_str)
//         return (NULL);
//     while (str[i])
//     {
//         if (str[i] == quotes)
//             i++;
//         new_str[i] = str[i];
//         i++;
//     }
//     new_str[i] = '\0';
//     return (new_str);    
// }