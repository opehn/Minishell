/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:14:15 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/30 16:15:22 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_data.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*head;

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
