/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:37:44 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/29 21:08:05 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//variable name has to be one of those alphanum || digit || _
// check if var_name is ?NULL
// ❗️ function that add text to the content of a var 
// ❗️ export test=hola -> export test+=same export ="holasame"
// a function that fix the tokens correctly for the export to export all passed variable

int is_correct(char *name)
{
    int i;

    i = 0;
    while (name[i])
    {
        if (ft_isalnum(name[i]) || name[i]== '_')
            i++;
        else
            return (0);
    }
    return (1);    
}