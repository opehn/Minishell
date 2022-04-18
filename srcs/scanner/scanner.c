#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int	scan_token(t_tree *root, t_env_list *env_list)
{
	int	 res;
	int	 *i;
	char	*data;
	char	**remain;

	if (!root->data)
		return (true);
	i = (int *)malloc(sizeof(int) * 1);
	remain = (char **) malloc(sizeof(char *) * 1);
	if (!i || !remain)
		exit_error(ERR_MALLOC);
	init_str(remain);
	*i = 0;
	res = 0;
	data = ft_strndup(root->data, ft_strlen(root->data));
	res = iterate_scan(data, remain, i, root, env_list);
	return (res);
}

int	 iterate_scan(char *data, char **remain, int *i, t_tree *root, t_env_list *env_list)
{
	int	 flag;
	int	 res;

	flag = 0;
	res = 0;
	ignore_space(data, i);
	while (data[*i] && !res)
	{
		flag = *i;
		res = if_quot(data, i, remain);
		if (res)
			return (res);
		res = if_red(data, i, remain, root, env_list);
		if (data[*i] == DS)
				expand_ds(data, i, remain, env_list);
		if (flag == *i) //if data[*i] is not special
		{
			if (data[*i] && data[*i] != ' ')
			{
				*remain = ft_strjoin_ch(*remain, data[*i]);
				(*i)++;
			}
			ignore_space(data, i);
			if (data[*i - 1] == ' ' && (*remain)[0])
				*remain = ft_strjoin_ch(*remain, ' ');
		}
	}
	grow_tree(NULL, *remain, root, 0, env_list);
	return (res);
}
