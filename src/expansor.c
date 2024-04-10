/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:38:28 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/10 20:43:36 by avolcy           ###   ########.fr       */
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

    i = -1;
    data_sp = ft_split(data, '$');
    if (!sh->env)
        sh->env = create_lst_env(env);
    new_data = NULL;
    while (data_sp[++i])
    {
        cpy_data = NULL;
        var_node = found_var(data_sp[i], sh->env);
        if (var_node)
        {   
            cpy_data = ft_strdup(var_node->var_content);
            new_data = ft_strjoin2(new_data, cpy_data);
        }
        else if (!var_node && new_data && data_sp[i])
            new_data = ft_strdup(new_data);  
        else 
            new_data = ft_strjoin2(new_data, data_sp[i]);  
    }
    if (data_sp)
        free(data_sp);
    return (new_data);
}
// bash-3.2$ "$USER"
// bash: avolcy: command not found
// bash-3.2$ "'$USER'"
// bash: 'avolcy': command not found
// bash-3.2$ "''$USER''"
// bash: ''avolcy'': command not found
// bash-3.2$ "'"'$USER'"'"
// bash: '$USER': command not found
// bash-3.2$ "'''$USER'''"
// bash: '''avolcy''': command not found
// bash-3.2$ ""'"'$USER'"'""
// bash: "avolcy": command not found
// bash-3.2$ ""'"$USER"'""
// bash: "$USER": command not found
// bash-3.2$ "'"$USER"'"
// bash: 'avolcy': command not found
// bash-3.2$
// bash-3.2$ ""'"$USER"'""
// bash: "$USER": command not found
// bash-3.2$ """'"$USER"'"""
// bash: 'avolcy': command not found
// bash-3.2$

// cd $HOME = cd follow by the home content
// echo $HOME print the HOME content 
// adsaddas$PWD to type 7
// “$PWD” to type 7
// parser expansor change the token and expand the data of the token
// and later in the parser the remove quotes
// remove the quotes of the same kind
// if starts with singles = 'hola'✅
// final token will be = hola
// if starts with  = 'e'ch'o'✅
// final token will be = echo
// 'ho"l"a'✅
// ho"l"a

// if (numsingle / 2) % 2 != 0 means impar
// if impar type  5

static int is_single(char *s)
{
    int i;

    i = 0;
    while (*s)
    {
        if (*s == '\'')
            i++;
        s++;
    }
    return (i);
}

static char *remove_single_quotes(char *str)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    tmp = malloc(sizeof(char) * (ft_strlen(str) - is_single(str)) + 1);
    if (!tmp)
        return (NULL);
    tmp[i] = '\0';
    j = 0;
    while (str[i])
    {
        if (!(str[i] == '\''))
            tmp[j++] = str[i];
        i++;
    }
    tmp[j] = '\0';
    return (tmp);
}

static bool all_single(char *s)
{
    bool all_sgl;

    all_sgl = true;
    while (*s)
    {
        if (*s != '\'' && (*s == '$' && ft_isalnum(*s)))
        {
            all_sgl = false;
            break ;
        }
        ++s;
    }
    return (all_sgl);
}

static void reasign_tok_type(t_token *tok)
{
    while (tok)
    {
        if (all_single(tok->data) == true)// && tok->data[0] == '\'')
        {
            if(is_single(tok->data) / 2 % 2 == 0)
                tok->type = 7;
            else
                tok->type = 5;
            if (tok->data[0] == '\'')
                tok->data = remove_single_quotes(tok->data);
        }
        tok = tok->next;
    }
    
}

void expansor(t_shell *sh, char **env)
{
    //int i;
    t_token *tok;

    //i = -1;
    tok = sh->tokens;
    while (tok)
    {
       reasign_tok_type(tok);
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