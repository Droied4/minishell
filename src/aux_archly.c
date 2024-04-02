/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_archly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:17:12 by deordone          #+#    #+#             */
/*   Updated: 2024/04/02 17:11:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if(!lst)
		return ;
    tmp = lst;
	if (1 == i)
	{
		while (tmp)
		{
        	printf("%s\n", tmp->line);
        	// printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        	// printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        	// printf("next----%p\n", (void *)tmp->next);
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
	return (0);}

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

void    init_shell(t_shell *sh)
{
    sh->env = NULL;
    sh->st_cmd = NULL;
    // sh->tokens = generate_tokens(line);
}
