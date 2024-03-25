/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:41:07 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/25 18:25:37 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo without nothing or -nnnn -n prints a \n
//echo with -n or -nnnnnnnnnnnnn or -nnnnnnnnnn n prints the prompt back
//echo with -nnnnnnnnnn n n prints : "n nbash", -nnnn nn n n : nn n nbash
//echo with  -nnnnn- || -nnn-n prints : -nnnnn- \n, -nnn-n \n
//echo with -nnnn -n
void    execute_echo(t_shell *sh)
{
    printf("Hola echo o o o o \n");

    if (sh->tokens->next->data == NULL)
        printf("\n");
}