/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/18 22:51:06 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

int	heredoc_cnt(t_forest *forest)
{
	int	i;

	i = 0;
	while (forest)
	{
		while (forest->root)
		{
			if (forest->root->left_child->type == HEREDOC)
				++i;
			forest->root = forest->root->right_child;
		}
		forest = forest->next;
	}
	return (i);
}

void	heredoc_chk(t_info *info)
{
	t_forest	*cur_forest;
	int			cnt;
	int			i;

	cur_forest = info->forest;
	cnt = heredoc_cnt(cur_forest);
	i = 0;
	while (i < cnt)
	{
		i++;
	}
}