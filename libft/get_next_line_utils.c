/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:39:37 by avolcy            #+#    #+#             */
/*   Updated: 2023/10/03 21:25:54 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*==================FT_CLEAN_UP===================*/
void	*ft_clean_up(char **alloc_mem)
{
	if (alloc_mem && *alloc_mem)
	{
		free(*alloc_mem);
		*alloc_mem = NULL;
	}
	return (NULL);
}
/*===================FT_STRLEN====================*/

/*size_t	ft_strlen(const char *string)
{
	size_t	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}
=================FT_STRCHR=======================

char	*ft_strchr(const char *string, int c)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (char)c)
			return ((char *)&string[i]);
		i++;
	}
	if ((string[i]) == (char)c)
		return ((char *)&string[i]);
	return (NULL);
}
*/
/*=================FT_STRJOIN=====================*/

char	*ft_strjoin2(char *storage, char *buffer)
{
	int		i;
	int		j;
	size_t	len;
	char	*new_storage;

	if (storage == NULL)
	{
		storage = malloc(sizeof(char) * 1);
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	len = ft_strlen(storage);
	new_storage = malloc(sizeof(char) * (ft_strlen(buffer) + len + 1));
	if (!new_storage)
		return (ft_clean_up(&storage));
	i = -1;
	while (storage[++i])
		new_storage[i] = storage[i];
	j = 0;
	while (buffer[j])
		new_storage[i++] = buffer[j++];
	new_storage[i] = '\0';
	ft_clean_up(&storage);
	return (new_storage);
}
