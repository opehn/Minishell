#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

extern int g_exit_status;

int expand_ds(char *data, int *i, char **remain, t_env_list *env_list, int quot_flag)
{
    //printf("expand data[%d] : %c\n", *i, data[*i]);
    if (quot_flag)
	{
		(*i)++;
		inside_quot_expand(data, i, remain, env_list);
        return (0);
	}
    (*i)++;
	if (data[*i] == D_QUOT || data[*i] == S_QUOT)
    {
        if_quot_expand(data, i, remain, env_list);
        return (1);
    }
    
    else
        no_quot_expand(data, i, remain, env_list);
    return (0);
}

void    inside_quot_expand(char *data, int *i, char **remain, t_env_list *env_list)
{
	//printf("inside_quot_expand\n");
	no_quot_expand(data, i, remain, env_list);
   //printf("after insied quot data[%d] : %c\n", *i, data[*i]);
}

void    no_quot_expand(char *data, int *i, char **remain, t_env_list *env_list)
{
    char *key;
    int  res;

    //printf("no_quot data[%d] : %c\n", *i, data[*i]);
    res = 0;
    key = make_key(data, i);
  //  printf("key : %s\n", key);
        if (key[0])
        {
            res = expand_if_match(i, key, remain, env_list);
            if (!res)
                (*i) += ft_strlen(key);
        }
        else
        {
	//		printf("here\n");
            *remain = ft_strjoin_ch(*remain, '$');
            (*i) += ft_strlen(key);
        }

}

char    *make_key(char *data, int *i)
{
    int start;
    int j;
    int key_len;
    int red_flag;

    start = *i;
    j = *i;
    key_len = 0;

    red_flag = chk_red(data, &j);
    while (data[j] && data[j] != ' '  && data[j] != S_QUOT && data[j] != D_QUOT && data[j] != DS && !red_flag)
    {
        j++;
        key_len++;
        red_flag = chk_red(data, &j);
    }
    //printf("make_key data[%d] : %c\n", j, data[j]);
    return (ft_substr(data, start, key_len));
}

int expand_if_match(int *i, char *key, char** remain, t_env_list *env_list)
{
    char *exit_status;

    if (!ft_strcmp(key, "?"))
    {
        exit_status = ft_itoa(g_exit_status);
        *remain = ft_strjoin(*remain, exit_status);
        *i += ft_strlen(exit_status);
        return (1);
    }
    while(env_list)
    {
        if(!ft_strcmp(env_list->key, key))
        {
            *remain = ft_strjoin(*remain, env_list->value); //append value to remain
            *i += ft_strlen(env_list->key);
            return (1);
        }
        env_list = env_list->next;
    }
    return (0);
}
