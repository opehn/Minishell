#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

extern int g_exit_status;

int expand_ds(char *data, int *i, char **res, t_env_list *env_list, int quot_flag)
{
	printf("expand_ds\n");
    (*i)++;
	if (quot_flag)
	{
		no_quot_expand(data, i, res, env_list);
		(*i)++;
		return (0);
	}
	if (data[*i] == D_QUOT || data[*i] == S_QUOT)
    {
        if_quot_expand(data, i, res, env_list);
        return (1);
    }
    else
        no_quot_expand(data, i, res, env_list);
    return (0);
}

void    no_quot_expand(char *data, int *i, char **res, t_env_list *env_list)
{
	printf("no_quot_expand_ds\n");
    char *key;
    int  result;

    result = 0;
    key = make_key(data, i);
        if (key[0])
        {
            result = expand_if_match(i, key, res, env_list);
            if (!result)
                (*i) += ft_strlen(key);
        }
        else
        {
            *res = ft_strjoin_ch(*res, '$');
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
    while (data[j] && data[j] != SEP  && data[j] != S_QUOT && data[j] != D_QUOT && data[j] != DS && !red_flag)
    {
        j++;
        key_len++;
        red_flag = chk_red(data, &j);
    }
    return (ft_substr(data, start, key_len));
}

int expand_if_match(int *i, char *key, char** res, t_env_list *env_list)
{
	printf("expand_if_match\n");
	printf("key : %s\n", key);
    if (!ft_strcmp(key, "?", ft_strlen(key), 1))
    {
        expand_exit_status(i, res);
        return (1);
    }
    while(env_list)
    {
        if(!ft_strcmp(env_list->key, key, ft_strlen(env_list->key), ft_strlen(key)))
        {
            *res = ft_strjoin(*res, env_list->value); //append value to remain
            *i += ft_strlen(env_list->key);
            return (1);
        }
        env_list = env_list->next;
    }
    return (0);
}

void    expand_exit_status(int *i, char **res)
{
	printf("expand_exit_status\n");
    char *exit_status;
	printf("i : %d\n", *i);

    exit_status = ft_itoa(g_exit_status);
    *res = ft_strjoin(*res, exit_status);
    (*i)++; 
	printf("i : %d\n", *i);

}
