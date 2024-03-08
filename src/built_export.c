/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/05 21:50:27 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env    *exporting_var(t_shell sh, t_env **lst_env)
{
    t_env   *new;
    t_env   *last;
    
    new = create_envnode(sh.tokens->next->data);
    if (new)
    {
        last = *lst_env;
        while(last->next)
            last = last->next;
        last->next = new;
    }
    return (*lst_env);
}

void    execute_export(t_shell *sh, char **env)
{
    int flag;
    t_env   *s_env;

    flag = 0;
    s_env = NULL;
    if (sh->tokens && sh->tokens->next)
    {
        printf("hola export\n");
        if (!s_env)
            s_env = create_lst_env(env);
        s_env = exporting_var(*sh, &s_env);
        flag = 1;
    }
    else if (!sh->tokens->next && flag > 0)
        s_env = create_lst_env(convert_to_dchar(s_env));
    else
        s_env = create_lst_env(env);
     print_lst_env(s_env, 2);
    //to put in alphabetic order function to do
}