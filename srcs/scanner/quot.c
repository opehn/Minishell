#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int if_quot(char *data, int *i, char **remain)
{
	char cur;

	cur = data[*i];
	if (cur == S_QUOT || cur == D_QUOT)
	{
		(*i)++;
		*remain = ft_strjoin_ch(*remain, cur);
		while(data[*i] && data[*i] != cur)
		{
			if (!data[*i])
				break;
			*remain = ft_strjoin_ch(*remain, data[*i]);
			(*i)++;
		}
		if (!data[*i])
			return (ERR_UNCLOSED);
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
	return (0);
}

int if_quot_expand(char *data, int *i, char **res, t_env_list *env_list)
{
//	printf("if_quot_expand\n");
    char cur;

    if (data[*i] == S_QUOT || data[*i] == D_QUOT)
    {
        cur = data[*i];
        (*i)++;
        if (cur == S_QUOT)
            find_next_sq(data, i, res);
        else if (cur == D_QUOT)
            find_next_dq(data, i, res, env_list);
        return (1);
    }
    return (0);
}

int find_next_sq(char *data, int *i, char **res)
{
	while (data[*i])
	{
		if (data[*i] == S_QUOT)
		{
			(*i)++; //move data idx from '
			break;
		}
		*res = ft_strjoin_ch(*res, data[*i]);
		(*i)++;
	}
	return (0);
}

int find_next_dq(char *data, int *i, char **res, t_env_list *env_list)
{
	int	start;

	while (data[*i])
	{
		//printf("remain[%d] : %c\n", *i, data[*i]);
		//printf("cmd : %s\n", *remain);
		start = *i;
		if (data[*i] == DS)
			expand_ds(data, i, res, env_list, 1);
		if (data[*i] == D_QUOT)
		{
			(*i)++; //move data idx from "
			break;
		}
		if (start == *i)
		{
			*res = ft_strjoin_ch(*res, data[*i]);
			(*i)++;
		}
	}
	return (0);
}