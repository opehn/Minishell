#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int find_next_sq(char *data, int *i, char **remain)
{
	while (data[*i])
	{
		if (data[*i] == S_QUOT)
		{
			(*i)++; //move data idx from '
			break;
		}
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
	return (0);
}

int find_next_dq(char *data, int *i, char **remain, t_env_list *env_list)
{

	while (data[*i])
	{
		if (data[*i] == D_QUOT)
		{
			(*i)++; //move data idx from "
			break;
		}
		if (data[*i] == DS)
			expand_ds(data, i, remain, env_list);
		if (data[*i] != D_QUOT)
			*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
	return (0);
}

void	ignore_space(char *data, int *i)
{
	if (data[*i] == ' ')
	{
		while(data[*i] == ' ')
			(*i)++;
	}
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
