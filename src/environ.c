/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:50:17 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 18:55:19 by avolcy           ###   ########.fr       */
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
}

t_env *create_envnode(char *envp)
{
    t_env *new;
    char    **splitting;
    
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return NULL;
    new->line = ft_strdup(envp); // Allocate memory and copy the string cause the 
    new->next = NULL;//new->line = envp only copy the pointer
    splitting = ft_split(new->line, '=');
    new->var_name = splitting[0];
    new->var_content = splitting[1];
    free(splitting);
    return new;
}

//pass the tokens to it///DONE !7h 56
t_env   *create_lst_env(char **envp)
{
    t_env  *new;
    t_env  *list_env; 
    
    printf("hola environ\n");
    int i;
    i = 0;
    list_env = NULL; // Initialize to NULL
    while (envp[i])// Separate increment operation from loop condition
     { 
        new = create_envnode(envp[i]);
        if (new)
            create_envlst(&list_env, new);
        i++;
    }
    // print_lst_env(list_env, 1); // Print the linked list
    return (list_env);
    // ft_del_env(&list_env);
    // return 0;
}

