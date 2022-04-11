#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int find_next_sq(char *data, int *i, char *remain)
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

		remain = ft_strjoin_ch(remain, data[*i]);
		(*i)++;
    }
	if (!quot_flag)
		return (ERR_UNCLOSED);
    return (0);
}

int find_next_dq(char *data, int *i, char *remain, t_env_list *env_list)
{
	int	quot_flag;

	quot_flag = 0;
    while (data[*i])
    {
		printf("quot- data[%d] : %c\n", *i, data[*i]);
        if (data[*i] == D_QUOT)
		{
			quot_flag = 1;
        	break;
		}
		if (data[*i] == DS)
			expand_ds(data, i, remain, env_list);
		remain = ft_strjoin_ch(remain, data[*i]);
		(*i)++;
    }
	if (!quot_flag)
		return (ERR_UNCLOSED);
    return (0);
}

int	expand_ds(char *data, int *i, char *remain, t_env_list *env_list)
{
	char	*key;
	int		key_len;

	key_len = 0;
	while (data[*i + 1] != ' ' || data[*i + 1] != '\0')
		key_len++;
	key = ft_substr(data, *i + 1, key_len);
	while(env_list->next)
	{
		if(!ft_strncmp(env_list->key, key, ft_strlen(env_list->key)))
		{
			remain = ft_strjoin(remain, env_list->value);

		}
		env_list = env_list->next;
	}
	*i += key_len;
	return (0);
}

int	chk_quote(char *data, int *i, char *remain, t_env_list *env_list)
{
	printf("chk_quote\n");
	int	res;

	res = 0;
	if (data[*i] == BS)
	{
		(*i)++;
		remain = ft_strjoin_ch(remain, data[*i]);
	}	
    else if (data[*i] == S_QUOT)
	{
		(*i)++;
		res = find_next_sq(data, i, remain);
	}
	
    else if (data[*i] == D_QUOT)
	{
		(*i)++;
		res = find_next_dq(data, i, remain, env_list);	
	}
	return (res);
}

void	chk_space(char *data, int *i, char *remain)
{
	if (*i != 0)
		*remain = ft_strjoin_ch(remain, ' ');
	while(data[*i + 1] == ' ')
		(*i)++;
	return ;
}

int	chk_red(char *data, int *i, char *remain, t_tree *root)
{
	char	*red_data;
	t_tree	*left_child;
	t_tree	*right_child;
	int		fn_len;
	int		start;

	(*i)++;
	fn_len = 0;
	start = *i;
		while(data[*i] != LEFT_RED && data[*i] != RIGHT_RED && ft_strncmp(ft_substr(data, *i, 2), ">>", 2) && data[*i] != '\0')
		{
			(*i)++;
			fn_len++;
		}	
		red_data = ft_substr(data, start, fn_len);
		while (root->right_child)
			root = root->right_child;

		left_child = init_tree(RED, red_data, NULL, NULL);
		root->left_child = left_child;
		if (remain)
			printf("remain : %s\n", remain);
		right_child = init_tree(BRANCH, remain, NULL, NULL);
		root->right_child = right_child;
		return (0);
}

bool	scan_token(t_tree *root, t_env_list *env_list)
{
	int		*i;
	char	*data;
	char	**remain;
	// int res;

	i = (int *)malloc(sizeof(int) * 1);
	remain = malloc(sizeof(char *) * 1);
	*remain = NULL;
	// *remain = malloc(sizeof (char) * 1);
	// remain[0] = '\0';
	if (!i)
		exit_error(ERR_MALLOC);
	// res = 0;
	data = ft_strndup(root->data, ft_strlen(root->data));
	*i = 0;
	while (data[*i])
	{
		// printf("data[%d] : %c\n", *i, data[*i]);
		if (data[*i] == BS || data[*i] == S_QUOT || data[*i] == D_QUOT)
			chk_quote(data, i, *remain, env_list);
		if (data[*i] == ' ')
			chk_space(data, i, *remain);
		if (data[*i] == LEFT_RED || data[*i] == RIGHT_RED || !ft_strncmp(ft_substr(data, *i, 2), ">>", 2))
			chk_red(data, i, *remain, root);
		if (data[*i] == '$')
			expand_ds(data, i, *remain, env_list);
		else
		{
			printf("char\n");
			*remain = ft_strjoin_ch(*remain, data[*i]);
		}
		if (*remain)
			printf("i : %d, remain : %s\n", *i, *remain);
		if(!data[*i])
			break;
		(*i)++;
	}
	return (true);
}
