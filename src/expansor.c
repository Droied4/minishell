/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:04:47 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/18 22:29:40 by avolcy           ###   ########.fr       */
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

    i = 0;
    while (*s)
    {
        if (*s == quotes)
            i++;
        s++;
    }
    return (i);
}

static char *remove_quotes(char *str, char quote)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    tmp = malloc(sizeof(char) * (ft_strlen(str) - number_of_quotes(str, quote)) + 1);
    if (!tmp)
        return (NULL);
    tmp[i] = '\0';
    j = 0;
    while (str[i])
    {
        if (!(str[i] == quote))
            tmp[j++] = str[i];
        i++;
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



// static void solve_double_quote(t_token *tok)
// {
//     int num_squotes;
//     // int num_dquotes;

//     while (tok)
//     {
//         num_squotes = number_of_quotes(tok->data, DQUOT);
//         if ((num_squotes % 2) == 0 && found_char(tok->data) == 1)
//         {
//             tok->data = remove_quotes(tok->data, DQUOT);
//             tok->type = 7;
//         }
//         tok = tok->next;
//     }
// }


//❌WITH TOKENS ⭕️
// static void solve_single_quote(t_token *tok)
// {
//     int num_quotes;
//     // int num_dquote;
   
//     while (tok)
//     {
//         // num_dquote = number_of_quotes(tok->data, dquote) / 2;
//         num_quotes = number_of_quotes(tok->data, SQUOT) / 2;
//         if((num_quotes % 2) == 0)
//             tok->type = 7;
//         else
//             tok->type = 5;
//         tok->data = remove_quotes(tok->data, SQUOT);
//         if (tok->data[0] == DQUOT && (num_quotes % 2) == 0)
//             tok->data = remove_quotes(tok->data, DQUOT);
//         tok = tok->next;
//     }
    
// }

//❌WITH TOKENS ⭕️
    // t_token *tok;

    // i = -1;
    // tok = sh->tokens;
    // while (tok)
    // {
    //      printf("this is the tok before EXP--->[%s]\n", tok->data);
    //     //CHECK IF TOKEN->DATA[0] IS " OR '
    //     if (tok->data[0] == '\'' && ft_strlen(tok->data) > 2)
    //         solve_single_quote(tok);
    //     else if (tok->data[0] == '\"' && ft_strlen(tok->data) > 2)
    //         solve_double_quote(tok);
    //    // if (tok->type == 7)
    //   // {
    //         // if (is_charmeta(tok->data[0]))
    //         if (found_char(tok->data) == 1)
    //             tok->data = expansion_var(sh, tok->data, env);
    //      printf("this is the tok after EXP--->[%s]\n", tok->data);
    //    //}
    //     tok = tok->next;
    // }

//AFTER PARSER ⭕️❌⭕️

// static char *smart_join(char *s)
// {}

// static int find_next_quote(char *s)
// {
//     int i;

//     i = 0;
//     if (s[i] == SQUOT)
//         i++;
//     while (s[i] && s[i] != SQUOT)
//         i++;
//     return (i);    
// }

// static char *filter_data(t_shell *sh, char *s, char **env)
// {
//     int i;
//     size_t len;
//     char *new;
//     char *save;

//     (void)sh;
//     (void)env;
//     new = NULL;
//     len = ft_strlen(s) - (size_t)number_of_quotes(s, SQUOT);
//     save =  malloc(sizeof(char) * len + 1);
//     if (!save)
//         return (NULL);
//     i = 0;
//     int pos =0;
//     while (s[i])
//     {
//         if (s[i] == SQUOT)
//         {
//             pos = find_next_quote(s);
//             printf("pos is [%d]\n", pos);
//             ft_strlcpy(save, s + 1, pos);
//             printf("pos is [%s]\n", save);
//             new = ft_strjoin2(new, save);
//         }
//         i++;
//     }
//     return (new);
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

char **smart_split(char *s)
{
    int i;
    int j;
    int flag;
    char *updated_s;


    i = 0;
    j = 0;
    flag = 0;
    updated_s = (char *)malloc(sizeof(char *) * (ft_strlen(s) * 2));
    if (!updated_s)
        return (NULL);
    updated_s[0] = '\0';
    while (s[i])
    {
        if ((s[i] == SQUOT || s[i] == DQUOT))// && flag == 0)
        {
            flag = 1;
            updated_s[j] = s[i];
            j++;
            i++;
        } 
        if ((s[i] == SQUOT || s[i] == DQUOT) && flag == 1)
        {
            flag = 0;
            updated_s[j] = ' '; 
            j++;
        }
        updated_s[j] = s[i];
        i++;
        j++;
    }
    updated_s[i] = '\0';
    printf("\tupdated_s  [%s]\n", updated_s);
    return (ft_split(updated_s, ' '));
}

char *filter_data(t_shell *sh, char *s, char **env)
{
    char **str;
    int i;
    size_t len;
    char *new;

    i = 0;
    len = 0;
    len = ft_strlen(s) - (size_t)number_of_quotes(s, SQUOT);
    str = smart_split(s);
    if (!str)
        return (NULL);

    while (str[i])
    {
        printf("\tthis is the current [%s]\n", str[i]);
        if (str[i][0] == DQUOT && found_char(str[i], '$'))
        {
            str[i] = remove_quotes(str[i], DQUOT);
            str[i] = expansion_var(sh, str[i], env);
        }
        else if (str[i][0] == SQUOT)
            str[i] = remove_quotes(str[i], SQUOT);
        i++;
    }
    // printf("\\----this is final len [%zu]\n", len);
    new = malloc(sizeof(char) * len + 1);
    if (!new)
        return (NULL);
    i = 0;
    new[i] ='\0';
    while (str[i])
    {
        new = ft_strjoin2(new, str[i]);
        i++;
    }
    free_matrix(str);
    return (new);
}

void expansor(t_shell *sh, char **env)
{
    int i;

    char **data;

    data = sh->words->cmd;
    i = 0;
    // bash-3.2$ '"""'dsdas"$USER"'"""'
    // bash: """dsdasavolcy""": command not found
    while (data[i]) 
    {
        printf("this is the tok before EXP--->[%s]\n", data[i]);
        data[i] = filter_data(sh, data[i], env);
        printf("this is the tok before EXP--->[%s]\n", data[i]);
        i++;
    }
}
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