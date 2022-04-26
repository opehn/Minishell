/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:21:29 by acho              #+#    #+#             */
/*   Updated: 2022/04/26 18:54:40 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "parsing.h"
#include "libft.h"

void	grow_red(char *red_data, int type, t_tree *root)
{
	t_tree	*left_child;
	t_tree	*right_child;

	while (root->right_child)
		root = root->right_child;
	left_child = init_tree(type, red_data, NULL, NULL);
	root->left_child = left_child;
	right_child = init_tree(BRANCH, NULL, NULL, NULL);
	root->right_child = right_child;
}

void	grow_cmd(char *remain, t_tree *root, t_env_list *env_list)
{
	t_tree	*left_child;
	t_tree	*right_child;
	char	*cmds[2];

	while (root->right_child)
		root = root->right_child;
	parse_cmd(remain, cmds, env_list);
	left_child = init_tree(CMD, cmds[0], NULL, NULL);
	root->left_child = left_child;
	right_child = init_tree(OPTARG, cmds[1], NULL, NULL);
	root->right_child = right_child;
}

void	parse_cmd(char *remain, char **cmds, t_env_list *env_list)
{
	char	**cmd;
	char	**opts;
	int		*i;

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
	int	start;

	while (remain[*i] && remain[*i] != SEP)
	{
		start = *i;
		if_quot_expand(remain, i, cmd, env_list);
		if (remain[*i] == DS)
			expand_ds(remain, i, cmd, env_list);
		if (start == *i)
		{
			if (remain[*i] && remain[*i] != D_QUOT && remain[*i] != S_QUOT
				&& remain[*i] != DS && remain[*i] != SEP)
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

	while (remain[*i])
	{
		start = *i;
		if_quot_expand(remain, i, opts, env_list);
		if (remain[*i] == DS)
			expand_ds(remain, i, opts, env_list);
		if (start == *i)
		{
			if (remain[*i] && remain[*i] != D_QUOT
				&& remain[*i] != S_QUOT && remain[*i] != DS)
			{
				*opts = ft_strjoin_ch(*opts, remain[*i]);
				(*i)++;
			}
		}
	}
}
