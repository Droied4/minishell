/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/02/23 15:55:50 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to print the list of tokens
void	print_tokens(t_token *lst)
{
	t_token *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("\nToken %i\n", tmp->index);
		printf("data----%s\n", tmp->data);
		printf("type----%i\n", tmp->type);
		printf("curr----%p\n", tmp);
		printf("prev----%p\n", tmp->prev);
		printf("next----%p\n", tmp->next);
		tmp = tmp->next;
	}
}

void	print_tablecmd(t_cmds *lst)
{
	int i;

	i = -1;
	t_cmds *tmp;

	tmp = lst;
	while (tmp)
	{
		printf(GREEN "\n-----------------------\n");
		printf(GREEN "| Table of Commands %i |\n", tmp->index);
		printf(GREEN "-----------------------\n");
		if (tmp->cmd)
		{
			printf(NC "cmd ->");
			while (tmp->cmd[++i])
				printf(NC " %s ", tmp->cmd[i]);
		}
		else 
			printf(RED "cmd -> NULL");
		printf(NC "\npath -> %s\n", tmp->path);
		printf("in_fd -> %i\n", tmp->in);
		printf("out_fd -> %i\n", tmp->out);
		printf(GREEN "---------------------\n");
		printf(NC "curr -> %p\n", tmp);
		printf(NC "next -> %p\n", tmp->next);
		printf(GREEN "---------------------\n");
		tmp = tmp->next;
	}
}

int	ft_deltoken(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

int	ft_delcmds(t_cmds **lst)
{
	t_cmds *temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->cmd)
			ft_free_array((*lst)->cmd);
		if ((*lst)->path)
			free((*lst)->path);
		if ((*lst)->in_file)
			free((*lst)->in_file);
		if ((*lst)->out_file)
			free((*lst)->out_file);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}

char	*ft_imp_strjoin(char const *s1, char const *s2)
{
	char	*rsv;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	rsv = malloc ((sizeof(char)) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
	return ((char *) rsv);
}

void	ft_free_array(char **res)
{
	int	i;

	i = 0;
	if (*res)
	{
		while (res[i])
			++i;
		while (i--)
			free(res[i]);
		free(res);
	}
}

// void init_env(char **envp)
// {
// 	int i = 0;
// 	t_node *new_node;

// 	while (envp[i])
// 	{
// 		create_node
// 	}
// }
