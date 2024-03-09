/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:42:37 by deordone          #+#    #+#             */
/*   Updated: 2024/03/09 04:08:26 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_type(t_token *lst)
{
	if (ft_strncmp(lst->data, "<<", 2) == 0)
		lst->type = DLESS;
	else if (ft_strncmp(lst->data, ">>", 2) == 0)
		lst->type = DGREAT;
	else if (ft_strncmp(lst->data, "<", 1) == 0)
		lst->type = LESS;
	else if (ft_strncmp(lst->data, ">", 1) == 0)
		lst->type = GREAT;
	else if (ft_strncmp(lst->data, "|", 1) == 0)
		lst->type = PIPE;
	else if (ft_strncmp(lst->data, "\'", 1) == 0)
		lst->type = SQUOTE;
	else if (ft_strncmp(lst->data, "\"", 1) == 0)
		lst->type = DQUOTE;
	else if (ft_strncmp(lst->data, "-", 1) == 0)
		lst->type = FLAG;
	else if (ft_strncmp(lst->data, "$", 1) == 0)
		lst->type = EXP;
	else
		lst->type = CMD;
}

int	cont_redir(char *s)
{
	int		i;
	int		j;
	int		count;
	char	*redir;

	i = -1;
	count = 0;
	redir = STR_REDIR;
	while (s[++i])
	{
		j = -1;
		while (redir[++j])
		{
			if (s[i] == redir[j])
				count++;
		}
	}
	return (count);
}

int	is_charedir(char c)
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

static char	*cpy_space(char *final_s, char *s, char btween)
{
	int	i;
	int	j;
	int h;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (is_charedir(s[i]) > 0)
		{
			h = 0;
			while (++h)
			{
				final_s[j++] = btween;
				if (h >= 2)
					break ;
				final_s[j++] = s[i];
				if (s[i] == s[i + 1])
					final_s[j++] = s[++i];
			}
		}
		else
			final_s[j++] = s[i];
	}
	return (final_s);
}

char	*add_between(char *s, char btween)
{
	int		len_str;
	char	*final_str;

	if (!s)
		return (NULL);
	//❗ in some cases appers a random P wtf ft_dprintf(2, "str -> %s\n", s);
	len_str = ft_strlen(s);
	len_str += cont_redir(s) * 2;
	final_str = malloc(sizeof(char) * len_str);
	if (!final_str)
		return (NULL);
	final_str = cpy_space(final_str, s, btween);
	final_str[len_str] = '\0';
//	ft_dprintf(2, "line -> %s\n", final_str);
	return (final_str);
}
