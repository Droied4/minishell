/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:22:14 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/06 22:24:00 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_words(char *str)
{
    int count;
    int is_sq;
    int is_dq;

    count = 0;
    is_sq = 0;
    is_dq = 0;
    while (*str)
    {
        count += 1;
        if (*str == SQUOT && !is_sq && !is_dq)
        {
            is_sq = 1;
            str++;
        }
        else if (*str == DQUOT && !is_dq && !is_sq)
        {
            is_dq = 1;
            str++;
        }
        while ((*str && is_sq && !is_dq && *str != SQUOT) ||
            (*str && !is_sq && is_dq && *str != DQUOT) ||
            (*str && !is_sq && !is_dq && *str != SQUOT && *str != DQUOT))
            str++;
        if ((is_sq || is_dq) && (*str == SQUOT || *str == DQUOT))
            str++;
    }
    return (count);
}

int get_len_string(char *str)
{
    int len;
    int sq;
    int dq;

    len = 0;
    sq = 0;
    dq = 0;
    if (*str == SQUOT)
    {
        sq = 1;
        len += 1;
    }
    else if (*str == DQUOT)
    {
        dq = 1;
        len += 1;
    }
    while ((str[len] && sq && !dq && str[len] != SQUOT) ||
        (str[len] && !sq && dq && str[len] != DQUOT) ||
        (str[len] && !sq && !dq && str[len] != SQUOT && str[len] != DQUOT))
        len++;
    if ((sq || dq) && (str[len] == SQUOT || str[len] == DQUOT))
        len += 1;
    return (len);    
}

char    *ft_get_cpy(char *str, int *pos)
{
    char    *cpy;
    int     len;
    int     i;

    len = get_len_string(str);
    *pos += len;
    cpy = malloc(sizeof(char) * (len + 1));
    if (!cpy)
        return (NULL);
    i = 0;
    while (i < len)
    {
        cpy[i] = str[i];
        i++;
    }
    cpy[i] = '\0';
    return (cpy);
}

char    **split_quotes(char *str)
{
    int i;
    int position;
    int words;
    char **smart_split;

    words = count_words(str);
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

int count_len(char *str)
{
    int len;
    
    len = 0;
    while (*str)
    {
      len += 1;
        if (*str != '$')
        {
          while (*str && *str != '$')
            str++;
        }
        else if (*str == '$')
        {
            str++;
            while (ft_isalnum(*str) || *str == '_')
                str++;
        }
    }
    return (len);
}

int count_len_env_part(char *str)
{
    int len;
    
    len = 0;
    if (*str != '$')
    {
        while (*str && *str != '$')
        {
            len++;
            str++;
        }
        return (len);
   }
   else if (*str == '$')
   {
    str++;
    while (ft_isalnum(*str) || *str == '_')
    {
        len++;
        str++;
    }
    return (len);
    }
}
char    *find_env_part(char *str, int *pos)
{
    int i;
    int len;
    char *part;

    len = count_len_env_part(str);
    *pos += len;
    part = malloc(sizeof(char) * (len + 1));
    i = 0;
    while (i < len)
    {
        part[i] = str[i];
        i++;
    }
    part[i] = '\0';
    return (part);
}

char **split_env_var(char *str)
{
    int i;
    int len;
    int position;
    char **splitted;

    len = count_len(str);
    splitted = malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (i < len)
    {
        splitted[i] = find_env_part(str , &position);
        str = &str[position];
        i++;
    }
    splitted[i] = NULL; 
    return (splitted);
}

char *expansion_data(t_shell *sh, char *str)
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
    while (env_split[i])
    {
        var_node = found_var(env_split[i], sh->env);
        if (var_node)
        {
            tmp = ft_strdup(var_node->var_content);
            env_split[i] = tmp;
        }
        i++;
    }
    tmp = join_split(env_split);
    free_matrix(env_split);
    return (tmp);
}

char    *expand_string(t_shell *sh, char *str)
{
    char    *expanded;

    if (str[0] == SQUOT)
    {
        str = ft_strtrim(str, "\'");
        return (str);
    }
    // if (!found_char(str, '$') && !found_char(str, '$') && !found_char(str, '$'))
        // return (ft_strdup(str));
    if (str[0] == DQUOT)
        str = ft_strtrim(str, "\"");
    if (found_char(str, '$'))
        str = expansion_data(sh, str);
    else
        str = ft_strdup(str);
    return (str);
}

char    *join_split(char **split)
{
    char    *join;
    char    *tmp;
    int     i;

    i = 0;
    join = NULL;
    while (split[i])
    {
        tmp = ft_strjoin2(join, split[i]);
        if (!tmp)
            return (free(join), NULL);
        join = tmp;
        i++;
    }
    return (join);
}

char    *expand_data(char *str)
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
        tmp = expand_string(smart_split[i]);
        if (!tmp)
            return (free_matrix(smart_split), NULL);
        free(smart_split[i]);
        smart_split[i] = tmp;
        i++;
    }
    
}

void	expansor_max(t_shell *sh, char **env)
{
    t_token *tok;

    tok = sh->tokens;
    while (tok)
    {
        if (found_char(tok->data, '$'))
        {
            char *tmp = expand_data(tok->data);
        }
        if (SQUOT || DQUOTE)
            trimmer_quote();
        tok = tok->next;
    }
        
}