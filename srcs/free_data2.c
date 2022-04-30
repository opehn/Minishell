#include "free_data.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_list *head;
	head = env_list;
	while (env_list)
	{
		free_env_node(env_list);
		env_list = env_list->next;
	}
	while (head)
	{
		free(head);
		head = head->next;
	}
}
