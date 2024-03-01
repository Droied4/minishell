/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:51:22 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/01 19:18:35 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exporting_var(t_shell sh, t_env **lst_env)
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
}