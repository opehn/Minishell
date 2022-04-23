#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int if_red(char *data, int *i, char **remain, t_tree *root, t_env_list *env_list)
{
	char	**red_data;
	int	 type;
	int	res;

	red_data = malloc(sizeof(char *) * 1);
	init_str(red_data);
	type = chk_red(data, i); //check red type
	if (type)
	{
		pass_sign(type, i); //move idx of data to file name
		ignore_space(data, i); 
		res = iter_red(data, i, red_data, env_list);
		if (res)
			return (res);
		grow_tree(*red_data, *remain, root, type, env_list);
	}
	return (0);
}

int		iter_red(char *data, int *i, char **red_data, t_env_list *env_list)
{

	int	 quot_flag;
	int	ds_flag;
	int	start;
	
	quot_flag = 0;
	ds_flag = 0;
	start = *i;
	while(!chk_red(data, i) && data[*i] != ' ' && data[*i])
	{
		start = *i;
		//printf("remain[%d] : %c\n", *i, data[*i]);
		quot_flag = if_quot_expand(data, i, red_data, env_list);
		if (data[*i] == DS)
		{
			ds_flag = 1;
			quot_flag = expand_ds(data, i, red_data, env_list, 0);
		}

		if (start == *i)
		{
			*red_data = ft_strjoin_ch(*red_data, data[*i]);
			(*i)++;
		}
	}
	if (!*red_data[0])
		return (chk_red_err(quot_flag, ds_flag));
	return (0);
}

int	chk_red_err(int	quot_flag, int ds_flag)
{
	if (!quot_flag && !ds_flag)
		return (ERR_SYNTAX);
	else if (!quot_flag && ds_flag)
		return (ERR_RED);
	else
		return (0);
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
