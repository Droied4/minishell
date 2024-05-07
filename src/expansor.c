/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:36:20 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/07 20:30:23 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *found_exp_var(char *str, t_env *lst)
{
    while (lst)
    {
        printf("content: %s\n", lst->var_content);
        if (ft_strncmp(str, lst->var_content, ft_strlen(str)))
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}

char *expansion_final(t_shell *sh, char *str)
{
    int i;
    char **env_split;
    t_env *var_node;
    char    *tmp;

    env_split = split_env_var(str);
    if (!env_split)
        return (NULL);
    // if (!sh->env)
        // sh->env = create_lst_env(sh->env);
    i = 0;
    printf("OKEY %p\n", env_split);
    while (env_split[i])
    {
        var_node = NULL;
        if (env_split[i][0] == '$')
            var_node = found_var(&env_split[i][1], sh->env);
        if (var_node)
        {
            tmp = ft_strdup(var_node->var_content);
            printf("this is join --->%s\n", tmp);
            env_split[i] = tmp;
        }
        i++;
    }
    tmp = join_split(env_split);
    printf("this is join --->%s\n", tmp);
    free_matrix(env_split);
    printf("final exp: %s\n", tmp);
    return (tmp);
}

char    *expand_string(t_shell *sh, char *str)
{
    char    *expanded;

    if (str[0] == SQUOT)
    {
        expanded = ft_strtrim(str, "\'");
        return (expanded);
    }
    // if (!found_char(str, '$') && !found_char(str, '$') && !found_char(str, '$'))
        // return (ft_strdup(str));
    if (str[0] == DQUOT)
        str = ft_strtrim(str, "\"");
    if (found_char(str, '$'))
    {
        expanded = expansion_final(sh, str);
        if (!ft_strncmp(expanded, str, ft_strlen(str)))
            expanded = ft_strdup("");
    }
    else
        expanded = ft_strdup(str);
    return (expanded);
}
char    **split_quotes(char *str)
{
    int i;
    int position;
    int words;
    char **smart_split;

    words = count_words(str, 0, 0);
    smart_split = malloc(sizeof(char *) * (words + 1));
    if (!smart_split)
        return (NULL);
    i = 0;
    position = 0;
    while (i < words)
    {
        smart_split[i] = ft_get_cpy(str, &position);
        str = &str[position];
        i++;
    }
    smart_split[i] = NULL;
    return (smart_split);
}
char    *expand_data(t_shell *sh, char *str)
{
    int     i;
    char    **smart_split;
    char    *tmp;

    smart_split = split_quotes(str);
    if (!smart_split)
        return (NULL);
    i = 0;
    while (smart_split[i])
    {
        tmp = expand_string(sh, smart_split[i]);
        if (!tmp)
            return (free_matrix(smart_split), NULL);
        free(smart_split[i]);
        smart_split[i] = tmp;
        i++;
    }
    tmp = join_split(smart_split);
    free_matrix(smart_split);
    return (tmp);
}

void	expansor(t_shell *sh)
{
    t_token *tok;
    char   *tmp;
    tok = sh->tokens;
    printf("dir env: %p\n", sh->env);
    while (tok)
    {
        if (!ft_strncmp("$?", tok->data, 2) || !ft_strncmp("$$", tok->data, 2))
            tok->data  = special_cases(tok->data, sh->exit_status);
        else if (found_char(tok->data, '$'))
        {
            tmp = expand_data(sh, tok->data);
            free(tok->data);// free
            tok->data = tmp;
        }
        else if (tok->data[0] == SQUOT || tok->data[0] == DQUOTE)
        {
            tmp = trimmer_quotes(tok->data, tok->data[0]);
            free(tok->data);// free
            tok->data = tmp;
        }
        tok = tok->next;
    }
}

// '"'$USER'"'
// "'$USER"'"'

/*CURIOUS WAY OF CALLING FUNCTION
result = concat("'", concat(username, "'"));
EXPECTED RESULT : "'"$USER"'"
bash-3.2$ echo  test  |  wc  -c
		5
bash-3.2$
'hola'"$USER"'"$USER"'"'$USER'"
 echo 'hola'  "     $USER    "  " a " "${USER}"
$'USER' $"USER"
echo $TERM ""hola$USER$USET$USERm > $USERg
ambiguous redirect*/