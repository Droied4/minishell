/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:29 by deordone          #+#    #+#             */
/*   Updated: 2024/03/08 17:23:04 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_shell(t_shell *sh)
{
    sh->env = NULL;
    sh->st_cmd = NULL;
    // sh->tokens = generate_tokens(line);
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

char	**convert_to_dchar(t_env *lst_env)
{
	int	i;
	char	**new;
	t_env	*tmp;

	new = (char **)malloc(sizeof(char *) * ((ft_lstenv_size(lst_env))) + 1);
	if (!new)
		return (NULL);
	tmp = lst_env;
	i = -1;
	while (tmp)
	{
		new[++i] = ft_strdup(tmp->line);
		tmp = tmp->next;
	}
	new[i] = NULL;
	return(new);
}
//to print the list of tokens
void	printlst(t_token *lst)
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

int	ft_del(t_token **lst)
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