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

printf("remain : %s\n", remain);
	i = malloc(sizeof(int) * 1);
	cmd = malloc(sizeof(char *) * 1);
	opts = malloc(sizeof(char *) * 1);
	init_str(cmd);
	init_str(opts);
	*i = 0;
	while (remain[*i] && remain[*i] != ' ')
	{
		if_quot_expand(remain, i, cmd, env_list);
		if (remain[*i] && remain[*i] != D_QUOT && remain[*i] != S_QUOT && remain[*i] != ' ')
		{
			*cmd = ft_strjoin_ch(*cmd, remain[*i]);
			(*i)++;
		}
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
