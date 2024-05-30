/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:37:32 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/30 18:33:46 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len += 1;
		if (*str != '$')
		{
			while (*str && *str != '$')
				str++;
		}
		else if (*str == '$')
		{
			str++;
			while (ft_isalnum(*str) || *str == '_')
				str++;
		}
	}
	return (len);
}

int	count_len_env_part(char *str)
{
	int	len;

	len = 0;
	if (*str != '$')
	{
		while (*str && *str != '$')
		{
			len++;
			str++;
		}
		return (len);
	}
	else if (*str == '$')
	{
		len++;
		str++;
		while (ft_isalnum(*str) || *str == '_')
		{
			len++;
			str++;
		}
	}
	return (len);
}

int	count_words(char *str, int count, int is_sq, int is_dq)
{
	while (*str)
	{
		is_sq = 0;
		is_dq = 0;
		count += 1;
		if (*str == SQUOT && !is_sq && !is_dq)
		{
			is_sq = 1;
			str++;
		}
		else if (*str == DQUOT && !is_dq && !is_sq)
		{
			is_dq = 1;
			str++;
		}
		while ((*str && is_sq && !is_dq && *str != SQUOT) || (*str && !is_sq
				&& is_dq && *str != DQUOT) || (*str && !is_sq && !is_dq
				&& *str != SQUOT && *str != DQUOT))
			str++;
		if ((is_sq || is_dq) && (*str == SQUOT || *str == DQUOT))
			str++;
	}
	return (count);
}

int	get_len_string(char *str)
{
	int	len;
	int	sq;
	int	dq;

	len = 0;
	sq = 0;
	dq = 0;
	if (*str == SQUOT)
	{
		sq = 1;
		len += 1;
	}
	else if (*str == DQUOT)
	{
		dq = 1;
		len += 1;
	}
	while ((str[len] && sq && !dq && str[len] != SQUOT) || (str[len] && !sq
			&& dq && str[len] != DQUOT) || (str[len] && !sq && !dq
			&& str[len] != SQUOT && str[len] != DQUOT))
		len++;
	if ((sq || dq) && (str[len] == SQUOT || str[len] == DQUOT))
		len += 1;
	return (len);
}
