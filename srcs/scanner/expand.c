#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>


int expand_ds(char *data, int *i, char **remain, t_env_list *env_list)
{
    (*i)++;
    if (data[*i] == D_QUOT || data[*i] == S_QUOT)
        if_quot_expand(data, i, remain, env_list);
    else
        no_quot_expand(data, i, remain, env_list);
    return (0);
}

void    no_quot_expand(char *data, int *i, char **remain, t_env_list *env_list)
{
    char *key;
    int  res;

    res = 0;
    key = make_key(data, i);
        if (key[0])
        {
            res = expand_if_match(i, key, remain, env_list);
            if (!res)
                (*i) += ft_strlen(key);
        }
        else
        {
            *remain = ft_strjoin_ch(*remain, '$');
            (*i) += ft_strlen(key);
        }

}

char    *make_key(char *data, int *i)
{
    int start;
    int j;
    int key_len;

    start = *i;
    j = *i;
    key_len = 0;

    while (data[j] != ' ' && data[j] != '\0' && data[j] != S_QUOT && data[j] != D_QUOT && data[j] != DS)
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
        if(!ft_strncmp(env_list->key, key, ft_strlen(key)))
        {
            *remain = ft_strjoin(*remain, env_list->value); //append value to remain
            *i += ft_strlen(env_list->key);
            return (1);
        }
        env_list = env_list->next;
    }
    return (0);
}
