/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/19 18:19:07 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

// int	heredoc_cnt(t_forest *forest)
// {
// 	int	i;

// 	i = 0;
// 	while (forest)
// 	{
// 		while (forest->root)
// 		{
// 			if (forest->root->left_child->type == HEREDOC)
// 				++i;
// 			forest->root = forest->root->right_child;
// 		}
// 		forest = forest->next;
// 	}
// 	return (i);
// }

void	init_heredoc_buf(t_info *info, char *end_word)
{
	
}

void	heredoc_chk(t_info *info)
{
	t_forest	*cur_forest;

	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	cur_forest = info->forest;
	while (cur_forest)
	{
		while (cur_forest->root)
		{
			if (cur_forest->root->left_child->type == HEREDOC)
				init_heredoc_buf(info, cur_forest->root->left_child->data);
			cur_forest->root = cur_forest->root->right_child;
		}
		cur_forest = cur_forest->next;
	}
}