/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dei.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 01:38:01 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("\nToken %i\n", tmp->index);
		printf("data -> %s\n", tmp->data);
		printf("type -> %i\n", tmp->type);
		printf("curr -> %p\n", tmp);
		printf("prev -> %p\n", tmp->prev);
		printf("next -> %p\n", tmp->next);
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
		printf(GREEN "\n-----------------------\n");
		printf(GREEN "|    Block Of Words   %i |\n", tmp->index);
		printf(GREEN "-----------------------\n");
	/*	if (tmp->type == 0)
			printf(NC "\ntype -> %s\n", "PIPE");
		else if (tmp->type == 1)
			printf(NC "\ntype -> %s\n", "REDIR");
		else if (tmp->type == 2)
			printf(NC "\ntype -> %s\n", "BUILT");
		else if (tmp->type == 3)
			printf(NC "\ntype -> %s\n", "SQUOTES");
		else if (tmp->type == 4)
			printf(NC "\ntype -> %s\n", "DQUOTES");
		else if (tmp->type == 5)
			printf(NC "\ntype -> %s\n", "COMMAND");
		else if (tmp->type == 6)
			printf(NC "\ntype -> %s\n", "FILE");*/
		if (tmp->cmd)
		{
			printf(NC "cmd ->");
			while (tmp->cmd[++i])
				printf(NC " %s ", tmp->cmd[i]);
		}
		else
			printf(RED "cmd -> NULL");
		printf("\npath -> %s\n", tmp->path);
		printf("in_fd -> %i\n", tmp->in);
		printf("out_fd -> %i\n", tmp->out);
		printf(GREEN "---------------------\n");
		printf(NC "curr -> %p\n", tmp);
		printf(NC "next -> %p\n", tmp->next);
		printf(GREEN "---------------------");
		printf(NC"\n");
		tmp = tmp->next;
	}
}

void	print_redir(t_redir *lst)
{
	int		i;
	t_redir	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = -1;
		printf(CYAN "\n-----------------------\n");
		printf(CYAN "|Block Of Redirections %i|\n", tmp->index);
		printf(CYAN "-----------------------\n");
	/*	if (tmp->type == 0)
			printf(NC "\ntype -> %s\n", "PIPE");
		else if (tmp->type == 1)
			printf(NC "\ntype -> %s\n", "REDIR");
		else if (tmp->type == 2)
			printf(NC "\ntype -> %s\n", "BUILT");
		else if (tmp->type == 3)
			printf(NC "\ntype -> %s\n", "SQUOTES");
		else if (tmp->type == 4)
			printf(NC "\ntype -> %s\n", "DQUOTES");
		else if (tmp->type == 5)
			printf(NC "\ntype -> %s\n", "COMMAND");
		else if (tmp->type == 6)
			printf(NC "\ntype -> %s\n", "FILE");*/
		printf(NC "type -> %i\n", tmp->type);
		if (tmp->file)
			printf(NC "file -> %s\n", tmp->file);
		else
			printf(RED "file -> NULL\n");
		printf(CYAN "---------------------\n");
		printf(NC "curr -> %p\n", tmp);
		printf(NC "next -> %p\n", tmp->next);
		printf(CYAN "---------------------");
		printf(NC"\n");
		tmp = tmp->next;
	}
}

char	*ft_imp_strjoin(char const *s1, char const *s2)
{
	char	*rsv;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	rsv = malloc((sizeof(char)) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!rsv)
		return (NULL);
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
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	ft_free_array(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i])
			++i;
		while (--i >= 0)
			free(res[i]);
		free(res);
		res = NULL;
	}
}
/*
static int	ft_cnt_word(const char *s, char c)
{
	int		i;
	int		word;
	int		count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count = 0;
		else if (count == 0)
		{
			count = 1;
			word++;
		}
		i++;
	}
	return (word);
}

static void	ft_free_array(char **res, int i)
{
	while (i--)
	{
		free(res[i]);
	}
	free(res);
}

static char	**ft_create(char const *s, char c, char **res)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		if (i > 0 && s[i] != c && s[i - 1] == c)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			res[j] = ft_substr(s, start, i - start + 1);
			if (!res[j])
			{
				ft_free_array(res, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = malloc(sizeof(char *) * (ft_cnt_word(s, c) + 1));
	if (!result)
		return (NULL);
	result = ft_create(s, c, result);
	return (result);
}

*/
