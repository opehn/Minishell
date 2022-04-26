/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:20:27 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 19:02:48 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parsing.h"

t_tree	*init_tree(int type, char *data, t_tree *left_child, \
					t_tree *right_child)
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
