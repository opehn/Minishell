#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int find_next_sq(char *data, int *i, char **remain)
{
	int closed_flag;

	closed_flag = 0;
	while (data[*i])
	{
		if (data[*i] == S_QUOT)
		{
			(*i)++; //move data idx from '
			closed_flag = 1;
			break;
		}
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
	if (!closed_flag)
		return (ERR_UNCLOSED);
	return (0);
}

int find_next_dq(char *data, int *i, char **remain, t_env_list *env_list)
{
	int closed_flag;

	closed_flag = 0;
	while (data[*i])
	{
		if (data[*i] == BS && (data[*i + 1] == DS || data[*i + 1] == BT || 
			data[*i + 1] == D_QUOT || data[*i + 1] == BS))
			pass_bs(data, i, remain);
		if (data[*i] == D_QUOT)
		{
			(*i)++; //move data idx from "
			closed_flag = 1;
			break;
		}
		if (data[*i] == DS)
		{
			(*i)++;
			expand_ds(data, i, remain, env_list, 1);
		}
		if (data[*i] != D_QUOT)
			*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
	if (!closed_flag)
		return (ERR_UNCLOSED);
	return (0);
}

char	*make_key(char *data, int *i, int quot_flag)
{
	int	start;
	int	key_len;
	int end_flag;

	start = 0;
	key_len = 0;
	end_flag = 0;
	if (!quot_flag)
		end_flag = (data[start] != ' ' && data[start] != '\0');
	if (quot_flag)
		end_flag = (data[start] != ' ' && data[start] != '\0' && data[start] != D_QUOT);
	start = *i;
	while (end_flag)
	{
		start++;
		key_len++;
		if (!quot_flag)
			end_flag = (data[start] != ' ' && data[start] != '\0');
		if (quot_flag)
			end_flag = (data[start] != ' ' && data[start] != '\0' && data[start] != D_QUOT);
	}
	return (ft_substr(data, *i, key_len));
}

int expand_if_match(char *data, int *i, char *key, char** remain, t_env_list *env_list)
{
	int	key_len;
	int	j;

	key_len = ft_strlen(key);
	j = 0;
	while(env_list)
	{
		if(!ft_strncmp(env_list->key, key, ft_strlen(env_list->key)))
		{
			*remain = ft_strjoin(*remain, env_list->value); //append value to remain
			*remain = ft_strjoin_ch(*remain, ' ');
			*i += key_len;
			return (1);
		}
		env_list = env_list->next;
	}
	while(j < key_len)
	{
		*remain = ft_strjoin_ch(*remain, data[*i]);
		j++;
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

void	pass_bs(char *data, int *i, char **remain)
{
	(*i)++;
	*remain = ft_strjoin_ch(*remain, data[*i]);
	(*i)++;
}

int if_quot(char *data, int *i, char **remain)
{
	char cur;

	cur = data[*i];
	if (cur == BS)
		pass_bs(data, i, remain);
	else if (cur == S_QUOT || cur == D_QUOT)
	{
		(*i)++;
		*remain = ft_strjoin_ch(*remain, cur);
		while(data[*i] && data[*i] != cur)
		{
			if ((data[*i] == BS  && cur == D_QUOT)
				&& data[*i + 1] == D_QUOT)
			{
				ft_strjoin(*remain, "\\\"");
				*i += 2;	
			}
			if (!data[*i])
				break;
			*remain = ft_strjoin_ch(*remain, data[*i]);
			(*i)++;
		}
		printf(" cur : data[%d] : %c\n", *i, data[*i]);
		if (!data[*i])
			return (ERR_UNCLOSED);
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
		*remain = ft_strjoin_ch(*remain, ' ');
	}
	return (0);
}
