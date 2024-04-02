/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dei.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 17:19:32 by deordone         ###   ########.fr       */
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

void	soft_exit(t_shell *sh)
{	
		ft_deltoken(&sh->tokens);
		ft_del_redirs(&sh->redir);
		ft_del_words(&sh->words);
		free(sh->line);
}

void	hard_exit(t_shell *sh)
{
		ft_deltoken(&sh->tokens);
		ft_del_redirs(&sh->redir);
		ft_del_words(&sh->words);
		clear_history();
		free(sh->line);
		exit(1);
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
		if (tmp->type == 0)
			printf(NC "\ntype -> %s\n", "PIPE");
		else if (tmp->type == 1)
			printf(NC "\ntype -> %s\n", "GREAT");
		else if (tmp->type == 2)
			printf(NC "\ntype -> %s\n", "LESS");
		else if (tmp->type == 3)
			printf(NC "\ntype -> %s\n", "DGREAT");
		else if (tmp->type == 4)
			printf(NC "\ntype -> %s\n", "DLESS");
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
