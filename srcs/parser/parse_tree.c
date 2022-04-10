#include "tree.h"
#include <stdio.h>

t_tree	*insert_tree(t_tree *root, char *data)
{
	if (root == NULL)
	{
		root = (t_tree *)malloc(sizeof(t_tree));
		root->left_child = NULL;
		root->right_child = NULL;
		root->data = data;
		return (root);
	}
	else
	{
		if (root->left_child != NULL)
			insert_tree(t_tree *root->left_child)
	}

}

int	init_tree(t_pipe_list *pipe)
{

}