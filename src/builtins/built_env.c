/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:07 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/09 22:24:24 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void create_envlst(t_env **lst, t_env *new)
{
    t_env *last;
    
    last = *lst;
    if (!(*lst))
    {
        *lst = new;
        return;
    }
    while (last->next)
        last = last->next;
    last->next = new;
    new->prev = last;
}

t_env *create_envnode(char *envp)
{
    t_env *new;
    char    **splitting;
    
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return NULL;
    new->line = ft_strdup(envp); 
    new->next = NULL;
    splitting = ft_split(new->line, '=');
    if (splitting)
    {
        new->var_name = splitting[0];
        new->var_content = splitting[1];
    }
    free(splitting);
    return (new);
}

t_env   *create_lst_env(char **envp)
{
    t_env  *new;
    t_env  *list_env; 
    
    int i;
    i = 0;
    list_env = NULL;
    while (envp[i])
     { 
        new = create_envnode(envp[i]);
        if (new)
            create_envlst(&list_env, new);
        i++;
    }
    return (list_env);
}

void    execute_env(t_shell *shell, char **env)
{
    if (shell->env == NULL)
	{
        shell->env = create_lst_env(env);
		print_lst_env(shell->env, 1);
	}
    else
		print_lst_env(shell->env, 1);
}
