/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 16:54:57 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env    *exporting_var(t_shell sh, t_env **lst_env)
{
    t_env   *new;
    t_env   *last;
    
    new = create_envnode(sh.tokens->next->data);
    //check if = is found in new for purposes
    if (new)
    {
        last = *lst_env;
        while(last->next)
            last = last->next;
        last->next = new;
    }
    return (*lst_env);
}
//clean code libro
void   execute_export(t_shell *sh, char **env)
{
    printf("hola export\n");
    //sh->env = create_lst_env(env);
    // if no params has passed means the 1st time
    //example shell > export  
    if (sh->tokens->next == NULL && sh->env == NULL)
        sh->env = create_lst_env(env);
    // if theres parameters passing within the export 1st time typing it
    //example shell > export hola 
    //2nda vez or N veces
    else if (sh->tokens->next == NULL && sh->env != NULL)
        print_lst_env(sh->env, 2);
    else if (sh->tokens->next != NULL && sh->env == NULL)
    {
        //create the list 
        //exporting the new variable
        sh->env = create_lst_env(env);
        sh->env = exporting_var(*sh, &sh->env); 
    }    
    else if (sh->tokens->next != NULL && sh->env != NULL)
    {
        printf("ooooooook\n");
        //add the new var
        sh->env = exporting_var(*sh, &sh->env); 
    } 
    //if export has been called before && want to add new vars

    
}
// print_lst_env(s_env, 2);
//to put in alphabetic order function to do
//while check_order == ko
//check 1st charact
//if 1st char == 1st->next char move to 2nd and so one
