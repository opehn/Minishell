#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int if_quot_expand(char *data, int *i, char **remain, t_env_list *env_list)
{
	char cur;

	if (data[*i] == S_QUOT || data[*i] == D_QUOT)
	{
		cur = data[*i];
		(*i)++;
		if (cur == S_QUOT)
			find_next_sq(data, i, remain);
		else if (cur == D_QUOT)
			find_next_dq(data, i, remain, env_list);
		return (1);
	}
	return (0);
}

int expand_ds(char *data, int *i, char **remain, t_env_list *env_list, int quot_flag)
{
	char	*key;

	key = make_key(data, i, quot_flag);
	if (!key[0])
		ft_strjoin_ch(*remain, '$');
	expand_if_match(data, i, key, remain, env_list);
	return (0);
}

int if_red(char *data, int *i, char **remain, t_tree *root, t_env_list *env_list)
{
	char	**red_data;
	int	 type;
	int	 quot_flag;

	red_data = malloc(sizeof(char *) * 1);
	init_str(red_data);
	type = 0;
	quot_flag = 0;
	type = chk_red(data, i); //check red type
	if (type)
	{
		if (type <= 2) //move idx of data to start of file name
			(*i) += 1;
		else if (type <= 4)
			(*i) += 2;
		ignore_space(data, i);
		while(!chk_red(data, i) && data[*i] != ' ' && data[*i])
		{
			quot_flag = if_quot_expand(data, i, red_data, env_list);
			if(chk_red(data, i) || data[*i] == ' ' || !data[*i])
				break;
			*red_data = ft_strjoin_ch(*red_data, data[*i]);

			(*i)++;
		}
		if (!*red_data[0] && !quot_flag)
			return (ERR_SYNTAX);
		grow_tree(*red_data, *remain, root, type, env_list);
		if (data[*i])
			*remain = ft_strjoin_ch(*remain, ' ');
	}
	return (0);
}

void	grow_tree(char *red_data, char *remain, t_tree *root, int res, t_env_list *env_list)
{
	t_tree  *left_child;
	t_tree  *right_child;
	char	*cmds[2];

	while (root->right_child)
		root = root->right_child;
	if (red_data) //if redirection
	{
		left_child = init_tree(res, red_data, NULL, NULL);
		root->left_child = left_child;
		right_child = init_tree(BRANCH, remain, NULL, NULL);
		root->right_child = right_child;
	}
	else //if cmd
	{
		parse_cmd(remain, cmds, env_list);
		left_child = init_tree(CMD, cmds[0], NULL, NULL);
		root->left_child = left_child;
		right_child = init_tree(OPTARG, cmds[1], NULL, NULL);
		root->right_child = right_child;
	}
}

void	parse_cmd(char *remain, char **cmds, t_env_list *env_list)
{
	char	**cmd;
	char	**opts;
	int	 *i;

	i = malloc(sizeof(int) * 1);
	cmd = malloc(sizeof(char *) * 1);
	opts = malloc(sizeof(char *) * 1);
	init_str(cmd);
	init_str(opts);
	*i = 0;
	while (remain[*i] && remain[*i] != ' ')
	{
		if(if_quot_expand(remain, i, cmd, env_list))
			break;
		*cmd = ft_strjoin_ch(*cmd, remain[*i]);
		(*i)++;
	}
	ignore_space(remain, i);
	while (remain[*i])
	{
		if_quot_expand(remain, i, opts, env_list);
		if (remain[*i] != S_QUOT && remain[*i] != D_QUOT)
		{
			*opts = ft_strjoin_ch(*opts, remain[*i]);
			if(remain[*i])
				(*i)++;
		}
	}
	cmds[0] = *cmd;
	cmds[1] = *opts;
}

void	init_str(char **str)
{
	*str = malloc(1);
	*str[0]= '\0';
}

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
	while (data[*i] && !res)
	{
		ignore_space(data, i);
		flag = *i;
		res = if_quot(data, i, remain);
		if (res)
			return (res);
		res = if_red(data, i, remain, root, env_list);
		if (data[*i] == DS)
			expand_ds(data, i, remain, env_list, 0);
		if (flag == *i) //if data[*i] is not special
		{
			if (data[*i] && data[*i] != ' ')
			{
				*remain = ft_strjoin_ch(*remain, data[*i]);
				(*i)++;
			}
			ignore_space(data, i);
			if (data[*i - 1] == ' ')
				*remain = ft_strjoin_ch(*remain, ' ');
		}
	}
	grow_tree(NULL, *remain, root, 0, env_list);
	return (res);
}
