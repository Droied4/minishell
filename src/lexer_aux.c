/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:42:37 by deordone          #+#    #+#             */
/*   Updated: 2024/03/20 15:59:31 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_token *lst)
{
	if (ft_strncmp(lst->data, "<<", 3) == 0)
		lst->type = DLESS;
	else if (ft_strncmp(lst->data, ">>", 2) == 0)
		lst->type = DGREAT;
	else if (ft_strncmp(lst->data, "<", 1) == 0 || ft_strncmp(lst->data, "<<<", 3) == 0)
		lst->type = LESS;
	else if (ft_strncmp(lst->data, ">", 1) == 0)
		lst->type = GREAT;
	else if (ft_strncmp(lst->data, "|", 1) == 0)
		lst->type = PIPE;
	else if (ft_strncmp(lst->data, "\'", 1) == 0)
		lst->type = SQUOTE;
	else if (ft_strncmp(lst->data, "\"", 1) == 0)
		lst->type = DQUOTE;
	else if (ft_strncmp(lst->data, "$", 1) == 0)
		lst->type = EXP;
	else
		lst->type = CMD;
}

int	cont_meta(char *s)
{
	int		i;
	int		j;
	int		count;
	char	*meta;

	i = -1;
	count = 0;
	meta = STR_META;
	while (s[++i])
	{
		j = -1;
		while (meta[++j])
		{
			if (s[i] == meta[j])
				count++;
		}
	}
	if (count != 0)
		return (++count);
	return (count);
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

static char	*cpy_space(char *final_s, char *s, char btween)
{
	int	i;
	int	j;
	int 	h;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_charmeta(s[i]) > 0) //&& s[i] != '$')
		{
			h = 0;
			while (++h)
			{
				final_s[j++] = btween;
				if (h >= 2)
					break ;
				final_s[j++] = s[i];
				if (s[i + 1] && s[i] == s[i + 1] && is_charmeta(s[i + 1]) > 0 && s[i] != '$' && s[i] != '\'' && s[i] != '\"') 
					final_s[j++] = s[++i];
				if (s[i + 1] && s[i] == s[i + 1]  && s[i] == '<') 
					final_s[j++] = s[++i];
				else if (s[i] == '$')
				{
					while(s[i + 1] != '\0' && s[i] != ' ')
					{
						final_s[j++] = s[++i];
					}
				}
			}
		}
		else
			final_s[j++] = s[i];
		i++;
	}
	return (final_s);
}

char	*add_between(char *s, char btween)
{
	int		len_str;
	char	*final_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	len_str += cont_meta(s) * 2;
	final_str = ft_calloc(sizeof(char),  len_str + 1);
	if (!final_str)
		return (NULL);
	final_str = cpy_space(final_str, s, btween);
	final_str[len_str] = '\0';
	free(s);
	return (final_str);
}
