#include "parsing.h"

t_node	*init_node(void)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));	
	new_node->node_content = NULL;
	new_node->left_content = NULL;
	new_node->right_content = NULL;
	return (new_node);
}

t_node	*init_tree(void)
{
	t_cmdtree *head;

	head = malloc(sizeof(t_cmdtree));
	head->cur = init_node;	
	head->next = NULL;
	return (head);
}

t_node	append_node(t_node *node)
{
	node->right = init_node;
}

void	make_tree(t_pipe_list *pipe)
{
	t_cmdtree	*head;
	char		*cur;

	head = init_tree();
	
	while(pipe->next)
	{
		cur = pipe->content;

	}
	
}
