/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:58 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 14:56:05 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

char	*setting_cmd(t_forest *forest)
{
	t_tree	*temp;

	temp = forest->root;
	while (temp)
	{
		if (temp->left_child && (temp->left_child->type == CMD))
			return (temp->left_child->data);
		temp = temp->right_child;
	}
	return (NULL);
}

void	pipe_setting(t_forest *cur_forest)
{
	if (cur_forest->prefd > -1)
	{
		dup2(cur_forest->prefd, 0);
		close(cur_forest->prefd);
	}
	if (cur_forest->next)
	{
		dup2(cur_forest->fd[IN], 1);
		close(cur_forest->fd[OUT]);
		close(cur_forest->fd[IN]);
	}
}
