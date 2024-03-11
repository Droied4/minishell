/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 18:17:20 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env    *exporting_var(t_shell sh, t_env **lst_env)
{
    int flag;
    size_t len;
    t_env   *new;
    t_env   *last;
    
    new = create_envnode(sh.tokens->next->data);
    //check if = is found in new
    //if true we add it to the env variables when env is passed
    //if not we just keep it in the export environment 
    //check if the new var_name is equal to the current var_name
    //if it s true we do a ft_strdup of the new content to the current 
    //and we return the list with the changed value
    //if not, we attach the new node at the end of the list
    len = 0; 
    flag = 0;
    if (new)
    {
        last = *lst_env;
        while(last->next)
        {
            len = ft_strlen(new->var_name);
            if (!ft_strncmp(last->var_name, new->var_name, len + 1))
            {
                flag = 1;
                last->var_content = ft_strdup(new->var_content);
                // if (last->next == NULL)
                //     break ;
            }
            last = last->next;
        }
        if (flag == 1)
        {
            free(new);
            return (*lst_env);
        }
        else
            last->next = new;
    }
    return (*lst_env);
}
//clean code libro
void   execute_export(t_shell *sh, char **env)
{
    int flag;
    printf("hola export\n");
    //sh->env = create_lst_env(env);
    // if no params has passed means the 1st time
    //example shell > export
    flag = 0;  
    if (sh->tokens->next == NULL && sh->env == NULL)
        sh->env = create_lst_env(env);
    // if theres parameters passing within the export 1st time typing it
    //example shell > export hola 
    //2nda vez or N veces
     else if (sh->tokens->next == NULL && sh->env != NULL)
    {
        //to put in alphabetic order function to do
        print_lst_env(sh->env, 2);
        flag = 1;
    }
    //if env command never passed before
    //means we just start with shell > export algo
    else if (sh->tokens->next != NULL && sh->env == NULL)
    {
        //create the list 
        //exporting the new variable
        sh->env = create_lst_env(env);
        sh->env = exporting_var(*sh, &sh->env); 
    }        
    else if (sh->tokens->next != NULL && sh->env != NULL)
    {
        //if export has been called before && want to add new vars
        printf("ooooooook\n");
        //add the new var
        sh->env = exporting_var(*sh, &sh->env); 
    }
    //to put in alphabetic order function to do
    if (flag == 0)
        print_lst_env(sh->env, 2);
}
//while check_order == ko
//check 1st charact
//if 1st char == 1st->next char move to 2nd and so one