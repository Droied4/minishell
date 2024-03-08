/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/03/08 20:05:44 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *lst)
{
	t_token *tmp;

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

void	print_tablecmd(t_cmds *lst)
{
	int i;

	t_cmds *tmp;

	tmp = lst;
	while (tmp)
	{
		i = -1;
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

int	is_meta(int type)
{
	static int	meta_char[] = META;
	int i;

	i = 8;
	while (--i >= -1)
	{
		if (type == meta_char[i])
			return (1);
	}
	return (-1);
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
	if (*res)
	{
		while (res[i])
			++i;
		while (i--)
			free(res[i]);
		free(res);
	}
}

char	**convert_to_dchar(t_env *lst_env)
{
	int	i;
	char	**new;
	t_env	*tmp;

	new = (char **)malloc(sizeof(char *) * ((ft_lstenv_size(lst_env))) + 1);
	if (!new)
		return (NULL);
	tmp = lst_env;
	while (tmp->next)
	{
		i = 0;
		new[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return(new);
}

void    print_lst_env(t_env *lst, int i)
{
    t_env *tmp;

    tmp = lst;
	if (1 == i)
	{
		while (tmp)
		{
        	printf("%s\n", tmp->line);
        	// printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        	// printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        	// printf("next----%p\n", (void *)tmp->next);
        	i++;
        	tmp = tmp->next;
		}
	}
	else if (2 == i)
	{
		//if var_content is (null) var_content = ""
		//if "="" don't comes after var_name only show var_name on export
		//if
		while (tmp)
		{
        	printf("declare -x %s=", tmp->var_name);
			if (!tmp->var_content)
        		printf("\"%s\"\n", "");
			else
				printf("\"%s\"\n", tmp->var_content);
        	// printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        	// printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        	// printf("next----%p\n", (void *)tmp->next);
        	i++;
        	tmp = tmp->next;
		}
	}
}
int	ft_del_env(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->line);
		free((*lst)->var_name);
		free((*lst)->var_content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	return (0);
}
int     ft_lstenv_size(t_env *lst)
{
        int             count;

        count = 0;
        if (!lst)
                return (count);
        while (lst != NULL)
        {
                count++;
                lst = lst->next;
        }
        return (count++);
}
