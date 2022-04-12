#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int find_next_sq(char *data, int *i, char **remain)
{
	int	quot_flag;

	quot_flag = 0;
    while (data[*i])
    {
        if (data[*i] == S_QUOT)
		{
			quot_flag = 1;
        	break;
		}
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
    }
	if (!quot_flag)
		return (ERR_UNCLOSED);
    return (0);
}

int find_next_dq(char *data, int *i, char **remain, t_env_list *env_list)
{
	int	quot_flag;

	quot_flag = 0;
    while (data[*i])
    {
        if (data[*i] == D_QUOT)
		{
			quot_flag = 1;
        	break;
		}
		if (data[*i] == DS)
			expand_ds(data, i, remain, env_list);
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
    }
	if (!quot_flag)
		return (ERR_UNCLOSED);
    return (0);
}

int	expand_ds(char *data, int *i, char **remain, t_env_list *env_list)
{
	char	*key;
	int		key_len;
	int		found;

	key_len = 0;
	found = 0;
	while (data[*i + 1] != ' ' || data[*i + 1] != '\0')
		key_len++;
	key = ft_substr(data, *i + 1, key_len);
	while(env_list)
	{
		if(!ft_strncmp(env_list->key, key, ft_strlen(env_list->key)))
			{
				*remain = ft_strjoin(*remain, env_list->value);
				found = 1;
			}
		env_list = env_list->next;
	}
	if (!found) // if no match
	{
		while(found++ <= key_len)
			{
				ft_strjoin_ch(*remain, data[*i]);
				(*i)++;
			}
	}
	else
		*i += key_len;
	return (0);
}

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

void	if_space(char *data, int *i, char **remain)
{
	if (data[*i] == ' ')
	{
		if (*i != 0)
			*remain = ft_strjoin_ch(*remain, ' ');
		while(data[*i + 1] == ' ')
			(*i)++;
	}
	return ;
}

int	chk_red(char *data, int *i)
{
	if (data[*i] == LD || data[*i] == RD)
		return (1);
	else if (!ft_strncmp(ft_substr(data, *i, 2), ">>", 2) ||  !ft_strncmp(ft_substr(data, *i, 2), "<<", 2))
		return (2);
	return (0);
}

int	if_red(char *data, int *i, char **remain, t_tree *root)
{
	char	*red_data;
	int		start;
	int		end;
	int		res;

	end = 0;
	res = 0;
	res = chk_red(data, i);
	if (res)
	{
		(*i) += res;
		start = *i;
		while(!chk_red(data, i) || data[*i] != '\0')
		{
			(*i)++;
			end++;
		}	
		red_data = ft_substr(data, start, end);
		grow_tree(red_data, remain, root);
	}
	return (0);
}

void	grow_tree(char *red_data, char **remain, t_tree *root)
{	
	t_tree	*left_child;
	t_tree	*right_child;

	while (root->right_child)
		root = root->right_child;
	left_child = init_tree(RED, red_data, NULL, NULL);
	root->left_child = left_child;
	right_child = init_tree(BRANCH, *remain, NULL, NULL);
	root->right_child = right_child;
	printf("right : %s\n", root->right_child->data);
}

bool	scan_token(t_tree *root, t_env_list *env_list)
{
	int		*i;
	char	*data;
	char	**remain;
	int		flag;
	int 	res;

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
	while (data[*i])
	{
		printf("data[%d] = ")
		flag = *i;
		res = if_quote(data, i, remain, env_list);
		if_space(data, i, remain);
		if_red(data, i, remain, root);
		if (data[*i] == '$')
			expand_ds(data, i, remain, env_list);
		if (flag == *i) //if data[*i] is unspecial
			*remain = ft_strjoin_ch(*remain, data[*i]);
		if(data[*i])
			(*i)++;
	}
	if (res)
		print_err(res);
	return (true);
}