/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:04:47 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/23 20:57:56 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int found_char(char *data, char c)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i] == c && data[i + 1])
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
        // else if (!var_node && new_data && data_sp[i])
        //     new_data = ft_strdup(new_data);  
        else 
            new_data = ft_strjoin2(new_data, data_sp[i]);  
    }
    if (data_sp)
        free(data_sp);
    return (new_data);
}

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

static int number_of_quotes(char *s, char quotes)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[j])
    {
        if (s[i] == quotes)
            i++;
        j++;
    }
    return (i);
}

// ''holas'''    len = 10   formula is ((len + (quote % 2)) - quotes
// 10 + 5 % 2 - 5 = 10 + 1 - 5 = 6

static char *remove_quotes(char *str, char quote)
{
    size_t i;
    int j;
    char *tmp;
    int num_quotes;

    tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!tmp)
        return (NULL);
    tmp[0] = '\0';
    j = 0;
    num_quotes = number_of_quotes(str, quote);
    if (num_quotes % 2 == 0)
    {
        while (*str != '\0')
        {
            if (!(*str == quote))
                tmp[j++] = *str;
            str++;
        }
    }
    else if (num_quotes % 2 != 0)
    {
        i = 1;
        while (*str != '\0')
        {
            if (*str != quote)
            {
                i++;
                tmp[j++] = *str;
            }
            else if (*str == quote && i == ft_strlen(str) + (num_quotes % 2) - num_quotes)
                tmp[j++] = *str;
            str++;
        }
    }
    tmp[j] = '\0';
    return (tmp);
}

// CURIOUS WAY OF CALLING FUNCTION
// result = concat("'", concat(username, "'"));
// EXPECTEDN RESULT : "'"$USER"'"

//DOUBLE QUOTES TESTS
// bash-3.2$ "'"$USER"'"
// bash: 'avolcy': command not found
// bash-3.2$ "'"'$USER'"'"
// bash: '$USER': command not found
// bash-3.2$ "'"'"'$USER'"'"'"
// bash: '"avolcy"': command not found
// bash-3.2$ """'"'"'$USER'"'"'"""
// bash: '"avolcy"': command not found
// bash-3.2$ ""'"'"'"'$USER'"'"'"'""
// bash: "'$USER'": command not found
// bash-3.2$ "'"'"'"'$USER'"'"'"'"
// bash: '"'avolcy'"': command not found
// bash-3.2$ "'"'"'"'"$USER"'"'"'"'"
// bash: '"'avolcy'"': command not found
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
// bash-3.2$ ""'"$USER"'""
// bash: "$USER": command not founds
// bash-3.2$ """'"$USER"'"""
// bash: 'avolcy': command not found
// bash-3.2$ "'"'"'$USER'"'"'"
// bash: '"avolcy"': command not found
// bash-3.2$ "'"$USER"'"
// bash: 'avolcy': command not found

static int find_next_quote(char *s, char c)
{
    int i;

    i = 0;
    if (s[i] == c)
        i++;
    while (s[i])
    {
        if (s[i] == c)
        {
            i++;
            break ;
        }
        i++;
    }
    return (i);    
}

static int find_next_pos(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != SQUOT && s[i] != DQUOT)
    {
        if (s[i] == SQUOT || s[i] == DQUOT)
        {
            i++;
            break ;
        }
        i++;
    }
    return (i);    
}

// 'hola'"$USER"'"$USER"'"'$USER'"

// static void add_dollar_case(char **s)
// {
//     int i;
//     int j;
//     char *new;

//     i = 0;
//     j = 0;
//     printf("this is s before putting dollar--->[%s]\n", *s);
//     new = malloc(sizeof(char) * ft_strlen(*s) * 2);
//     if (!new)
//         return ((void)NULL);
//     while (*s[i])
//     {
//         if (*s[i] == SQUOT && ft_isprint(*s[i + 1]) && *s[i + 1] != SQUOT)
//         {
//             new[j] = *s[i];
//             new[j++] = '$';
//         }
//         else if (*s[i + 1] == SQUOT && *s[i + 1] && *s[i] != SQUOT)
//             new[j++] = '$';
//         new[j++] = *s[i];
//         i++;
//     }
//     new[j] = '\0';
//     *s = new;
//     printf("this is s after putting dollar--->[%s]\n", *s);
// }

static char *string_modifier(t_shell *sh, char *s, char **env)
{
    int i;
    char *new_string;

(void)sh;
(void)env;
    i = 0;
    new_string = NULL;
    if (s[0] == SQUOT)
        new_string = remove_quotes(s, SQUOT);
    printf("this is new_string {%s}\n", new_string);
    return new_string;
    // else if (s[0] == DQUOT)
    // {
    //     new_string = remove_quotes(*s, DQUOT);
    //     if (found_char(new_string, SQUOT))
    //     {
    //         add_dollar_case(&new_string);
    //         new_string = expansion_var(sh, new_string, env);
    //     }
    //     else
    //         new_string =  expansion_var(sh, *s, env);
    // }
    // else
    //     new_string = expansion_var(sh, *s, env);
}

static char *filter_data(t_shell *sh, char *s, char **env)
{
    int pos;
    char *new;
    char *save;
(void)sh;
(void)env;
    new = NULL;
    save =  malloc(sizeof(char) * ft_strlen(s)+ 1);
    if (!save)
        return (NULL);
    pos = 0;
    save[0] = '\0';
    while (*s != '\0')
    {
        if (*s == SQUOT || *s == DQUOT)
        {
            pos =  pos + find_next_quote(s, *s);
            ft_strlcpy(save, s, pos + 1);
        }
        else 
        {
            s = s + pos;
            pos =  pos + find_next_pos(s);
            ft_strlcpy(save, s, pos + 1);
        }
        printf("this is save before modifier--->[%s\t%p]\n", save ,save);
        save = string_modifier(sh, save, env);
        printf("this is save after modifier--->[%s]\n", save);
        new = ft_strjoin2(new, save);
        save[0] = '\0';
        s = s + pos;
        pos = 0;
    }
    free(save);
    return (new);
}

// ❌WITH TsOKENS ⭕️
void expansor(t_shell *sh, char **env)
{
    int i;
    t_token *tok;

    i = -1;
    tok = sh->tokens;
    while (tok)
    {
         printf("this is the tok before EXP--->[%s]\n", tok->data);
         if (found_char(tok->data, SQUOT) || found_char(tok->data, DQUOT) || \
          found_char(tok->data, '$'))
         {
            tok->data = filter_data(sh, tok->data, env);            
         }
         printf("this is the tok after EXP--->[%s]\n", tok->data);
        tok = tok->next;
    }
}

//AFTER PARSER ⭕️❌⭕️

// static char *smart_join(char *s)
// {}


//     // str = '"""'dsdas"$USER"'"""'
//     // while (str[i]) {
//     //     if (str[i] == SQUOT || str[i] == DQUOT) {
//     //         int pos = find_next_quote(str[i + 1]);
//     //         str[pos] = '\0';
//     //         char *save = ft_strdup(&str[i + 1]);
//     //         i = pos;
//     //     }
//     //     i++;
//     // }
    
// }


// char **smart_split(char *s)
// {
//     int i;
//     int j;
//     int s_flag;
//     int d_flag;
//     char *updated_s;


//     i = 0;
//     j = 0;
//     s_flag = 0;
//     d_flag = 0;
//     updated_s = (char *)malloc(sizeof(char *) * (ft_strlen(s) * 2));
//     if (!updated_s)
//         return (NULL);
//     updated_s[0] = '\0';
//     while (s[i])
//     {
//         if (s[i] == SQUOT && s_flag == 0 && d_flag == 0)
//             s_flag = 1;
//         else if (s[i] == DQUOT && s_flag == 0 && d_flag == 0)
//             d_flag = 1;
//         else if (s[i] == SQUOT && s_flag == 1 && d_flag == 0)
//         {
//             s_flag = 0;
//             updated_s[j++] = s[i];
//             updated_s[j++] = ' ';
//         }
//         else if (s[i] == DQUOT && s_flag == 0 && d_flag == 1)
//         {
//             d_flag = 0;
//             updated_s[j++] = s[i];
//             updated_s[j++] = ' ';
//         }
//         if (s[i] != '\0')
//             updated_s[j++] = s[i];
//         i++;
//     }
//     updated_s[j] = '\0';
//     printf("\t\tupdated_s  [%s]\n", updated_s);
//     return (ft_split(updated_s, ' '));
// }

// char *filter_data(t_shell *sh, char *s, char **env)
// {
//     char **str;
//     int i;
//     size_t len;
//     char *new;

//     i = 0;
//     len = 0;
//     len = ft_strlen(s) - (size_t)number_of_quotes(s, SQUOT);
//     str = smart_split(s);
//     if (!str)
//         return (NULL);

//     while (str[i])
//     {
//         printf("\tthis is the current [%s]\n", str[i]);
//         if (str[i][0] == DQUOT && found_char(str[i], '$'))
//         {
//             str[i] = remove_quotes(str[i], DQUOT);
//             str[i] = expansion_var(sh, str[i], env);
//         }
//         else if (str[i][0] == SQUOT)
//             str[i] = remove_quotes(str[i], SQUOT);
//         i++;
//     }
//     // printf("\\----this is final len [%zu]\n", len);
//     new = malloc(sizeof(char) * len + 1);
//     if (!new)
//         return (NULL);
//     i = 0;
//     new[i] ='\0';
//     while (str[i])
//     {
//         new = ft_strjoin2(new, str[i]);
//         i++;
//     }
//     free_matrix(str);
//     return (new);
// }

// void expansor(t_shell *sh, char **env)
// {
//     int i;

//     char **data;

//     data = sh->words->cmd;
//     i = 0;
//     // bash-3.2$ '"""'dsdas"$USER"'"""'
//     // bash: """dsdasavolcy""": command not found
//     while (data[i]) 
//     {
//         printf("this is the tok before EXP--->[%s]\n", data[i]);
//         data[i] = filter_data(sh, data[i], env);
//         printf("this is the tok before EXP--->[%s]\n", data[i]);
//         i++;
//     }
// }
// bash-3.2$ '"'"$USER"'"'
// bash: "avolcy": command not found
// bash-3.2$ '"$USER"'
// bash: "$USER": command not found
// bash-3.2$ ''"'"$USER"'"''
// bash: 'avolcy': command not found
// bash-3.2$ ''""'"$USER"'""''
// bash: "$USER": command not found
// bash-3.2$ ''"'"$USER"'"''
// bash: ""$USER"": command not found
// bash-3.2$ '""'""'"$USER"'""'""'
// bash: """$USER""": command not found
// bash-3.2$ '"'"""'"$USER"'"""'"'
// bash: "'avolcy'": command not found