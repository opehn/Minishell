#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int find_next_sq(char *data, int *i, char **remain)
{
    int quot_flag;

    quot_flag = 0;
    while (data[*i])
    {
        if (data[*i] == S_QUOT)
        {
            (*i)++; //move data idx from '
            quot_flag = 1;
            break;
        }
        *remain = ft_strjoin_ch(*remain, data[*i]);
        (*i)++;
    }
    if (!quot_flag)
        return (ERR_UNCLOSED);
    return (0);
}

int find_next_dq(char *data, int *i, char **remain, t_env_list *env_list)
{
    int quot_flag;

    quot_flag = 0;
    while (data[*i])
    {
        if (data[*i] == D_QUOT)
        {
            (*i)++; //move data idx from "
            quot_flag = 1;
            break;
        }
        if (data[*i] == DS)
        {
            (*i)++;
            expand_ds(data, i, remain, env_list);
        }
        if (data[*i] != D_QUOT)
            *remain = ft_strjoin_ch(*remain, data[*i]);
        (*i)++;
    }
    if (!quot_flag)
        return (ERR_UNCLOSED);
    return (0);
}

int find_value(char *data, int *i, char** remain, t_env_list *env_list, int *key_len)
{
    char    *key;
    int     start;

    start = *i;
    while (data[start] != ' ' && data[start] != '\0' && data[start] != D_QUOT)
    {
        start++;
        (*key_len)++;
    }
    key = ft_substr(data, *i, *key_len);
    while(env_list)
    {
        if(!ft_strncmp(env_list->key, key, ft_strlen(env_list->key)))
        {
            *remain = ft_strjoin(*remain, env_list->value); //append value to remain
            *remain = ft_strjoin_ch(*remain, ' ');
            return (1);
        }
        env_list = env_list->next;
    }
    return (0);
}

void    ignore_space(char *data, int *i)
{
    if (data[*i] == ' ')
    {
        while(data[*i] == ' ')
            (*i)++;
    }
    return ;
}

int chk_red(char *data, int *i)
{
    if (!ft_strncmp(ft_substr(data, *i, 2), ">>", 2))
        return (3);
    else if (!ft_strncmp(ft_substr(data, *i, 2), "<<", 2))
        return (4);
    else if (data[*i] == LD)
        return (1);
    else if (data[*i] == RD)
        return (2);
    return (0);
}

int if_quot(char *data, int *i, char **remain)
{
    char cur;

    cur = data[*i];
    if (cur == BS || cur == S_QUOT || cur == D_QUOT)
    {
        (*i)++;
        if (cur == BS)
        {
            *remain = ft_strjoin_ch(*remain, data[*i]);
            (*i)++;
        }
        else
        {
            *remain = ft_strjoin_ch(*remain, cur);
            while(data[*i] && data[*i] != cur)
            {
                *remain = ft_strjoin_ch(*remain, data[*i]);
                (*i)++;
            }
            if (!data[*i])
                return (ERR_UNCLOSED);
            *remain = ft_strjoin_ch(*remain, data[*i]);
            (*i)++;
        }
    }
    return (0);
}