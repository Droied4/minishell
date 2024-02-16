/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:31:55 by avolcy            #+#    #+#             */
/*   Updated: 2023/11/07 17:46:32 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	t_len;
	size_t	i;

	if (!s1)
		t_len = ft_strlen(s2) + 1;
	if (!s2)
		t_len = ft_strlen(s1) + 1;
	t_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((t_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

/*size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
char *ft_strjoin(char const *s1, char const *s2) {
    if (!s1 && !s2)
        return (NULL);

    size_t len1 = (s1 == NULL) ? 0 : ft_strlen(s1);
    size_t len2 = (s2 == NULL) ? 0 : ft_strlen(s2);

    size_t t_len = len1 + len2;
    char *res = (char *)malloc((t_len + 1) * sizeof(char));
    if (!res)
        return (NULL);

    size_t i = 0;
    while (i < len1) {
        res[i] = s1[i];
        i++;
    }
    size_t j = 0;
    while (j < len2) {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    return (res);
}

if (!s1 || !s2)
    {
        if (s1)
            return (ft_strdup(s1));
        else if (s2)
            return (ft_strdup(s2));
        else
            return (ft_strdup("");
    }*/
