/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:09:53 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/10 18:09:54 by taeheoki         ###   ########.fr       */
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

void	parsing_tree(t_info *info, t_pipe_list *pipe)
{
	int	i;
	int	pipe_cnt;
	t_tree	**pipe_tree;

	pipe_cnt = count_tree(pipe);
	printf("pipe_cnt : %d in parsing_tree\n", pipe_cnt);
	pipe_tree = (t_tree **)malloc(sizeof(t_tree *) * pipe_cnt);
	if (!pipe_tree)
		exit_error(ERR_MALLOC);
	info->root = pipe_tree;
	i = 0;
	while (i < pipe_cnt)
	{
		pipe_tree[i] = init_tree(0, pipe->pipe_data, NULL, NULL);
		// info->forest->root = init_tree(0, pipe->pipe_data, NULL, NULL);
		printf("pipe_tree[%d] : %s\n", i, pipe_tree[i]->data);
		printf("before scan_token check in parsing_tree\n");
		if (scan_token(pipe_tree[i], info->env_list) == false)
			exit_error(ERR_TOKENIZE);
		printf("after scan_token check in parsing_tree\n");
		i++;
		pipe = pipe->next;
		// 
	}
}