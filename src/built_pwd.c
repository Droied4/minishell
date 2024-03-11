/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:13:30 by avolcy            #+#    #+#             */
/*   Updated: 2024/03/11 18:19:02 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
// pwd
void    execute_pwd()
{
    char *s;

    s = NULL;
    s = getcwd(s, 50);
    printf("%s\n", s);

    // return 0;
}