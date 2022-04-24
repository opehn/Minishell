/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:09:53 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/24 15:58:27 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "error.h"
#include <stdio.h>
#include "env.h"
#include "parsing.h"
#include "scanner.h"

t_tree	*init_tree(int type, char *data, t_tree *left_child, t_tree *right_child)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		exit_error(ERR_MALLOC);
	tree->type = type;
	tree->data = data;
	tree->left_child = left_child;
	tree->right_child = right_child;
	return (tree);
}

void	delete_tree(t_tree *tree)
{
	t_tree	*left_child;
	t_tree	*right_child;

	if (tree == NULL)
		return ;
	left_child = tree->left_child;
	right_child = tree->right_child;
	free(tree);
	tree = 0;
	if (tree->left_child != NULL)
		delete_tree(left_child);
	if (tree->right_child != NULL)
		delete_tree(right_child);
}

int	count_tree(t_pipe_list *pipe)
{
	int	cnt;

	cnt = 0;
	while (pipe)
	{
		cnt++;
		pipe = pipe->next;
	}
	return (cnt);
}

t_forest	*init_forest(t_tree *pipe_tree)
{
	t_forest	*forest;

	forest = (t_forest *)malloc(sizeof(t_forest));
	if (!forest)
		exit_error(ERR_MALLOC);
	forest->root = pipe_tree;
	forest->next = NULL;
	forest->prefd = -1;
	return (forest);
}

int		parsing_tree(t_info *info, t_pipe_list *pipe)
{
	int			i;
	t_tree		**pipe_tree;
	t_forest	*temp;
	int			res;

	res = 0;
	info->pipe_cnt = count_tree(pipe);
	pipe_tree = (t_tree **)malloc(sizeof(t_tree *) * info->pipe_cnt);
	if (!pipe_tree)
		exit_error(ERR_MALLOC);
	info->root = pipe_tree;
	i = -1;
	while (++i < info->pipe_cnt)
	{
		pipe_tree[i] = init_tree(0, pipe->pipe_data, NULL, NULL);
		printf("pipe_tree[%d] : %s\n", i, pipe_tree[i]->data);
		res = scan_token(pipe_tree[i], info->env_list);
		if (res)
			return (res);
		if (i == 0)
		{
			info->forest = init_forest(pipe_tree[i]);
			temp = info->forest;
		}
		else if (i < info->pipe_cnt)
		{
			info->forest->next = init_forest(pipe_tree[i]);
			info->forest = info->forest->next;
		}
		pipe = pipe->next;
	}
	info->forest = temp;
	return (0);
}
