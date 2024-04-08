/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:38:28 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/08 18:45:44 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int found_dollar(char *data)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i] == '$' && data[i + 1])
            return (1);
        i++;
    }
    return (0);
}

char     *expansion_var(t_shell *sh, char *data, char **env)
{
    int i;
    t_env *var_node;
    char *cpy_data;
    char *new_data;
    char **data_sp;

    i = 0;
    data_sp = ft_split(data, '$');
    if (!sh->env)
        sh->env = create_lst_env(env);
    new_data = NULL;
    while (data_sp[i])
    {
        cpy_data = NULL;
        var_node = found_var(data_sp[i], sh->env);
        if (var_node && is_expandable(data_sp[i]))// cant be there cause split $
        {   
            cpy_data = ft_strdup(var_node->var_content);
            new_data = ft_strjoin2(new_data, cpy_data);
        }
        else
            new_data = ft_strdup(data_sp[i]);  
        i++;
    }
    if (data_sp)
        free(data_sp);
    return (new_data);
}
// cd $HOME = cd follow by the home content
// echo $HOME print the HOME content 
// adsaddas$PWD to type 7
// “$PWD” to type 7
// '$PWD' maintain in the SQUOTES TYPE
// parser expansor change the token and expand the data of the token
// and later in the parser the remove quotes
// remove the quotes of the same kind
// if starts with singles = 'hola'
// final token will be = hola
// if starts with  = 'e'ch'o'
// final token will be = echo
// 'ho"l"a'
// ho"l"a

static int is_expandable(char *data)
{
    int len;

    len = ft_strlen(data);
    if (data[0] == '\"' && data[len] == '\"')
        return (1);
    return (0);
}

void expansor(t_shell *sh, char **env)
{
    //int i;
    t_token *tok;

    //i = -1;
    tok = sh->tokens;
    while (tok)
    {
        reasign_tok_type(&tok);
        if (tok->type == 7)
        {
            // if (is_charmeta(tok->data[0]))
            if (found_dollar(tok->data) == 1)
                tok->data = expansion_var(sh, tok->data, env);
         printf("this is the value--->[%s]\n", tok->data);
        }
        tok = tok->next;
    }
}