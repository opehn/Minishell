#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int if_quot_expand(char *data, int *i, char **remain, t_env_list *env_list)
{
    char cur;

    if (data[*i] == S_QUOT || data[*i] == D_QUOT)
    {
        cur = data[*i];
        (*i)++;
        if (cur == S_QUOT)
            find_next_sq(data, i, remain);
        else if (cur == D_QUOT)
            find_next_dq(data, i, remain, env_list);
        return (1);
    }
    return (0);
}

int expand_ds(char *data, int *i, char **remain, t_env_list *env_list)
{
    char    *key;

    (*i)++;
    key = make_key(data, i);
    if (key[0])
        expand_if_match(i, key, remain, env_list);
    if (!key[0])
    {
        *reman = ft_strjoin_ch(*remain, '$');
        (*i) += ft_strlen(key);
    }
    return (0);
}

char    *make_key(char *data, int *i)
{
    int start;
    int j;
    int key_len;

    start = *i;
    j = *i;
    key_len = 0;

    while (data[j] != ' ' && data[j] != '\0' && data[j] != D_QUOT && data[j] != DS)
    {
        j++;
        key_len++;
    }
    return (ft_substr(data, start, key_len));
}

int expand_if_match(int *i, char *key, char** remain, t_env_list *env_list)
{
    while(env_list)
    {
        if(!ft_strncmp(env_list->key, key, ft_strlen(env_list->key)))
        {
            *remain = ft_strjoin(*remain, env_list->value); //append value to remain
            *i += ft_strlen(env_list->key);
        }
        env_list = env_list->next;

    }
    return (0);
}
