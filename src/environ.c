/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:50:17 by avolcy            #+#    #+#             */
/*   Updated: 2024/02/22 16:34:31 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env {
    char    *line;//for test purpose
    char    *var_name;
    char    *var_content;
    struct s_env *next;
}   t_env;

void create_envlst(t_env **lst, t_env *new) {
    t_env *last;
    
    last = *lst;
    if (!(*lst)) {
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
void printlst(t_env *lst) {
    t_env *tmp;
    
    tmp = lst;
    int i = 0;
    while (tmp) {
        printf("\t\nline --[%i]--- is [%s]\n",i , tmp->line);
        printf("\tNAME ------------ is[%s]\n", tmp->var_name);
        printf("\tCONTENT -------- is [%s]\n", tmp->var_content);
        //printf("next----%p\n", (void *)tmp->next);
        i++;
        tmp = tmp->next;
    }
}
//pass the tokens to it 

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    t_env  *new;
    t_env  *list_env;
    

    int i;
    i = 0;
    list_env = NULL; // Initialize to NULL
    while (envp[i]) { // Separate increment operation from loop condition
        new = create_envnode(envp[i]);
        if (new)
            create_envlst(&list_env, new);
            
        i++;
    }
    printlst(list_env); // Print the linked list
    ft_del_env(&list_env);
    return 0;
}
