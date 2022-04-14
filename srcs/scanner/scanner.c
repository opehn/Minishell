#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int	if_quote(char *data, int *i, char **remain, t_env_list *env_list)
{
	int	res;
	char cur;

	res = 0;
	if (data[*i] == BS || data[*i] == S_QUOT || data[*i] == D_QUOT)
	{
		cur = data[*i];
		(*i)++;
		if (cur == BS)
			*remain = ft_strjoin_ch(*remain, data[*i]);
		else if (cur == S_QUOT)
			res = find_next_sq(data, i, remain);
		else if (cur == D_QUOT)
			res = find_next_dq(data, i, remain, env_list);
	}
	return (res);
}

int	expand_ds(char *data, int *i, char **remain, t_env_list *env_list)
{
	int		*key_len;
	int		k;

	key_len = (int *)malloc(sizeof(int) * 1);
	*key_len = 0;
	k = 0;
	(*i)++;
	if (find_value(data, i, remain, env_list, key_len))
		*i += *key_len; //move idx of data
	else 
	{
		while(k < *key_len)
			{
				*remain = ft_strjoin_ch(*remain, data[*i]);
				k++;
				(*i)++;
			}
	}
	return (0);
}

int	if_red(char *data, int *i, char **remain, t_tree *root, t_env_list *env_list)
{
	char	**red_data;
	int		res;

	red_data = malloc(sizeof(char *) * 1);
	*red_data = malloc(1);
	*red_data[0] = '\0';
	res = 0;
	res = chk_red(data, i); //check red type
	if (res)
	{
		if (res <= 2) //move idx of data to start of file name
			(*i) += 1;		
		else if (res <= 4)
			(*i) += 2;
		ignore_space(data, i);
		while(!chk_red(data, i) && data[*i] != ' ' && data[*i])
		{
			res = if_quote(data, i, red_data, env_list);
			printf("after quote data[%d] : %d\n", *i, data[*i]);
			*red_data = ft_strjoin_ch(*red_data, data[*i]);
			if (data[*i]) //quotechk paases idx to null
				(*i)++;
		}	
		grow_tree(*red_data, *remain, root, res);
	}
	return (res);
}

void	grow_tree(char *red_data, char *remain, t_tree *root, int res)
{	
	t_tree	*left_child;
	t_tree	*right_child;
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
		parse_cmd(remain, cmds);
		left_child = init_tree(CMD, cmds[0], NULL, NULL);
		root->left_child = left_child;
		right_child = init_tree(OPTARG, cmds[1], NULL, NULL);
		root->right_child = right_child;
	}
}

void	parse_cmd(char *remain, char **cmds)
{
	char	*cmd;
	char	*opts;
	int		i;
	
	i = 0;
	cmd = malloc(1);
	opts = malloc(1);
	cmd[0] = '\0';
	opts[0] = '\0';
	while (remain[i] && remain[i] != ' ')
	{
		cmd = ft_strjoin_ch(cmd, remain[i]);
		i++;
	}
	if (remain[i] && remain[i + 1] == ' ')
	{
		while (remain[i] && remain[i] == ' ')
		{
			cmd = ft_strjoin_ch(cmd, remain[i]);
			i++;
		}
	}
	else if (remain[i] == ' ')
		i++;
	while (remain[i])
	{
		opts = ft_strjoin_ch(opts, remain[i]);
		i++;
	}
	cmds[0] = cmd;
	cmds[1] = opts;
}

bool	scan_token(t_tree *root, t_env_list *env_list)
{
	int		*i;
	char	*data;
	char	**remain;
	int		flag;
	int 	res;

	if (!root->data)
		return (true);
	i = (int *)malloc(sizeof(int) * 1);
	remain = (char **) malloc(sizeof(char *) * 1);
	*remain = (char *) malloc(sizeof (char) * 1);
	if (!i || !remain || !*remain)
		exit_error(ERR_MALLOC);
	*remain[0] = '\0';
	flag = 0;
	res = 0;	
	*i = 0;
	data = ft_strndup(root->data, ft_strlen(root->data));
	while (data[*i] == ' ')
		(*i)++;
	while (data[*i])
	{
		printf("data[%d] : %c\n", *i, data[*i]);
		flag = *i;
		ignore_space(data, i);
		if (data[*i] == BS || data[*i] == S_QUOT || data[*i] == D_QUOT)
		{
			res = if_quote(data, i, remain, env_list);
			if (data[*i])
				*remain = ft_strjoin_ch(*remain, ' ');
		}
		if_red(data, i, remain, root, env_list);
		if (data[*i] == '$')
			expand_ds(data, i, remain, env_list);
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
	grow_tree(NULL, *remain, root, 0);
	if (res)
		print_err(res);
	return (true);
}
