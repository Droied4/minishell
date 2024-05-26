/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:06:19 by deordone          #+#    #+#             */
/*   Updated: 2024/05/25 16:42:57 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *data)
{
	int		i;
	char	**builtins;

	builtins = ft_split(STR_BUILTINS, ' ');
	i = -1;
	while (builtins[++i])
	{
		if (ft_strncmp(data, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
		{
			ft_free_array(builtins);
			return (1);
		}
	}
	ft_free_array(builtins);
	return (-1);
}

int	is_char_redir(char c)
{
	char	*redir;
	int		i;

	i = -1;
	redir = STR_REDIR;
	while (redir[++i])
	{
		if (c == redir[i])
			return (1);
	}
	return (-1);
}

int	is_charmeta(char c)
{
	char	*meta;
	int		i;

	i = -1;
	meta = STR_META;
	while (meta[++i])
	{
		if (c == meta[i])
			return (1);
	}
	return (-1);
}

int	is_meta(int type)
{
	int	*meta;
	int	i;

	meta = malloc(sizeof(int) * 8);
	if (!meta)
		exit(1);
	i = -1;
	while (++i <= 7)
		meta[i] = i;
	while (--i > -1)
	{
		if (type == meta[i] || type == DGREAT || type == DLESS)
		{
			free(meta);
			return (1);
		}
	}
	free(meta);
	return (-1);
}

int	is_redir(int type)
{
	int	*redir;
	int	i;

	redir = malloc(sizeof(int) * 3);
	if (!redir)
		exit(1);
	i = -1;
	while (++i <= 2)
		redir[i] = i;
	while (--i > -1)
	{
		if (type == redir[i] || type == DGREAT || type == DLESS)
		{
			free(redir);
			return (1);
		}
	}
	free(redir);
	return (-1);
}
