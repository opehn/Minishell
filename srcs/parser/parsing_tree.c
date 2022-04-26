/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:09:53 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 19:02:28 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parsing.h"
#include "scanner.h"

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

t_forest	*setting_forest(t_info *info, t_tree **pipe_tree, int i, \
							t_forest *temp)
{
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
	return (temp);
}

int	parsing_tree(t_info *info, t_pipe_list *pipe)
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
		res = scan_token(pipe_tree[i], info->env_list);
		if (res)
			return (res);
		temp = setting_forest(info, pipe_tree, i, temp);
		pipe = pipe->next;
	}
	info->forest = temp;
	return (0);
}
