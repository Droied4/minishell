/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dei.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/06/13 20:11:32 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_imp_strjoin(char const *s1, char const *s2)
{
	char	*rsv;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	rsv = malloc((sizeof(char)) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!rsv)
		exit(1);
	while (s1[i])
	{
		rsv[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		rsv[i] = s2[i2];
		i++;
		i2++;
	}
	rsv[i] = '\0';
	free((void *)s1);
	free((void *)s2);
	return ((char *)rsv);
}

char	*char2str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		exit(1);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	stock_of(t_shell *sh, int type)
{
	t_token	*tok;
	int		stock;

	stock = 0;
	tok = sh->tokens;
	while (tok)
	{
		if (tok->type == type)
			stock++;
		tok = tok->next;
	}
	return (stock);
}

int	char_is_inside(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	**get_envivar(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, 5) == 0)
			return (ft_split(env[i], ':'));
		i++;
	}
	return (NULL);
}

/*void	print_tokens(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_dprintf(1, "\nToken %i\n", tmp->index);
		ft_dprintf(1, "data -> %s\n", tmp->data);
		ft_dprintf(1, "type -> %i\n", tmp->type);
		ft_dprintf(1, "curr -> %p\n", tmp);
		ft_dprintf(1, "prev -> %p\n", tmp->prev);
		ft_dprintf(1, "next -> %p\n", tmp->next);
		tmp = tmp->next;
	}
}

void	print_words(t_words *lst)
{
	int		i;
	t_words	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = -1;
		ft_dprintf(1,GREEN "\n-----------------------\n");
		ft_dprintf(1,GREEN "|    Block Of Words   %i |\n", tmp->index);
		ft_dprintf(1,GREEN "-----------------------\n");
		if (tmp->cmd)
		{
			ft_dprintf(1,NC "cmd ->");
			while (tmp->cmd[++i])
				ft_dprintf(1,NC " %s ", tmp->cmd[i]);
		}
		else
			ft_dprintf(1,RED "cmd -> NULL");
		ft_dprintf(1, "\npath -> %s\n", tmp->path);
		ft_dprintf(1, "in_fd -> %i\n", tmp->in);
		ft_dprintf(1, "out_fd -> %i\n", tmp->out);
		ft_dprintf(1, GREEN "---------------------\n");
		ft_dprintf(1, NC "curr -> %p\n", tmp);
		ft_dprintf(1, NC "next -> %p\n", tmp->next);
		ft_dprintf(1, GREEN "---------------------");
		ft_dprintf(1, NC "\n");
		tmp = tmp->next;
	}
}

void	print_redir(t_redir *lst)
{
	t_redir	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_dprintf(1, CYAN "\n-----------------------\n");
		ft_dprintf(1, CYAN "|Block Of Redirections %i|\n", tmp->index);
		ft_dprintf(1, CYAN "-----------------------\n");
		if (tmp->type == 0)
			ft_dprintf(1, NC "\ntype -> %s\n", "PIPE");
		else if (tmp->type == 1)
			ft_dprintf(1, NC "\ntype -> %s\n", "GREAT");
		else if (tmp->type == 2)
			ft_dprintf(1, NC "\ntype -> %s\n", "LESS");
		else if (tmp->type == 3)
			ft_dprintf(1, NC "\ntype -> %s\n", "DGREAT");
		else if (tmp->type == 4)
			ft_dprintf(1, NC "\ntype -> %s\n", "DLESS");
		if (tmp->file)
			ft_dprintf(1, NC "file -> %s\n", tmp->file);
		else
			ft_dprintf(1, RED "file -> NULL\n");
		ft_dprintf(1, CYAN "---------------------\n");
		ft_dprintf(1, NC "curr -> %p\n", tmp);
		ft_dprintf(1, NC "next -> %p\n", tmp->next);
		ft_dprintf(1, CYAN "---------------------");
		ft_dprintf(1, NC "\n");
		tmp = tmp->next;
	}
}*/
