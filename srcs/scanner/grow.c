#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

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
	make_cmd(remain, env_list, cmd, i);
	ignore_space(remain, i);
	make_opts(remain, env_list, opts, i);
	cmds[0] = *cmd;
	cmds[1] = *opts;
}

void	make_cmd(char *remain, t_env_list *env_list, char **cmd, int *i)
{
	printf("make_Cmd\n");
	int	start;

	while (remain[*i] && remain[*i] != SEP)
	{
		start = *i;
		if_quot_expand(remain, i, cmd, env_list);
		if (remain[*i] == DS)
				expand_ds(remain, i, cmd, env_list, 0);
		if (start == *i)
		{
			if (remain[*i] && remain[*i] != D_QUOT && remain[*i] != S_QUOT && remain[*i] != DS && remain[*i] != SEP)
			{
				*cmd = ft_strjoin_ch(*cmd, remain[*i]);
				(*i)++;
			}
		}
	}
}

void	make_opts(char *remain, t_env_list *env_list, char **opts, int *i)
{
	int	start;

	printf("remain : %s\n", remain);
	while (remain[*i])
	{
		printf("remain[%d] : %c\n", *i, remain[*i]);
		start = *i;
		if_quot_expand(remain, i, opts, env_list);
		if (remain[*i] == DS)
				expand_ds(remain, i, opts, env_list, 0);
		if (start == *i)
		{
			if (remain[*i] && remain[*i] != D_QUOT && remain[*i] != S_QUOT && remain[*i] != DS)
			{
				*opts = ft_strjoin_ch(*opts, remain[*i]);
				(*i)++;
			}
		}
	}
}
