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
	int	 quot_flag; //

	red_data = malloc(sizeof(char *) * 1);
	init_str(red_data);
	type = 0;
	quot_flag = 0;
	type = chk_red(data, i); //check red type
	if (type)
	{
		pass_sign(type, i); //move idx of data to file name
		ignore_space(data, i);
		while(!chk_red(data, i) && data[*i] != ' ' && data[*i])
		{
			quot_flag = if_quot_expand(data, i, red_data, env_list);
			if(chk_red(data, i) || data[*i] == ' ' || !data[*i])
				break;
			if (data[*i] == DS)
				expand_ds(data, i, red_data, env_list);
			if(chk_red(data, i) || data[*i] == ' ' || !data[*i])
				break;
			*red_data = ft_strjoin_ch(*red_data, data[*i]);
			(*i)++;
		}
		if (!*red_data[0] && !quot_flag)
			return (ERR_SYNTAX);
		grow_tree(*red_data, *remain, root, type, env_list);
		if (data[*i] && *remain[0] && *remain[ft_strlen(*remain)] != ' ') 
			*remain = ft_strjoin_ch(*remain, ' ');
	}
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