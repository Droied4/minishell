/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:24:56 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/08 13:45:18 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo without nothing or -nnnn -n prints a \n
//echo with -n or -nnnnnnnnnnnnn or -nnnnnnnnnn n prints the prompt back
//echo with -nnnnnnnnnn n n prints : "n nbash", -nnnn nn n n : nn n nbash
//echo with  -nnnnn- || -nnn-n prints : -nnnnn- \n, -nnn-n \n
//echo with -nnnn -n

//to DELETE ❌❌
static  int num_tok(t_token *tok)
{
    int i;

    i = 0;
    while (tok)
    {
        i++;
        tok = tok->next;
    }
    return (i);
}

static char **toks_to_dchar(t_token *tok, int x)
{
    char **res;
    int num;
    
    num = num_tok(tok);
    res = NULL;
    res = (char **)malloc(sizeof(char **) * num + 1);
    if (!res)
    {
        while (res[x])
        {
            free(res[x]);
            x++;
        }
        free(res);
    }
    x = 0;
    while (x < num - 1)
    {
        tok = tok->next;
        if (tok)
            res[x] = ft_strdup(tok->data);
        x++;
    }
    return (res[x] = NULL, res);
}

static int is_flag(char *str)
{
    int i;
    
    i  = 0;
    if (str == NULL)
        return (0);
    if (str[0] == '-' && str[1])
    {
        i++;
        while(str[i])
        {
            if (str[i] != 'n')
                return (0);
            i++;
        }
        return (1);
    }
    return (0);
}

void   execute_echo(t_shell *sh)
{
    int i;
    char **matrix;
    int flags;
 
    i = 0;
    flags = 0;
    matrix = toks_to_dchar(sh->tokens, 0);
    while (is_flag(matrix[i]))
    {
            flags++;
            i++;
    }
    while (matrix[i])
    {
        if (matrix[i + 1])
            ft_dprintf(STDOUT_FILENO,"%s ",matrix[i]);
        else
            ft_dprintf(STDOUT_FILENO,"%s",matrix[i]);
        i++;
    }
    if (!flags)
        ft_dprintf(STDOUT_FILENO, "\n");
    free_matrix(matrix);
}
