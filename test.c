#include <stdio.h>
#include <stdlib.h>
#define SQUOT '\''
#define DQUOT '\"'

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


int count_words(char *str, int is_sq, int is_dq)
{
    int count;
    
    count = 0;
    while (*str)
    {
        is_sq = 0;
        is_dq = 0;
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

char    **split_quotes(char *str)
{
    int i;
    int position;
    int words;
    char **smart_split;

    words = count_words(str, 0, 0);
    printf("word: %d\n", words);
    smart_split = malloc(sizeof(char *) * (words + 1));
    if (!smart_split)
        return (NULL);
    i = 0;
    position = 0;
    while (i < words)
    {
        smart_split[i] = ft_get_cpy(str, &position);
        printf("splitqtes[%d] %s\n", i, smart_split[i]);
        str = &str[position];
        i++;
    }
    smart_split[i] = NULL;
    return (smart_split);
}

int main(void)
{
  char **split = split_quotes("\'hola\'\'\"$USER\"\'hola");
  return 0;
}
