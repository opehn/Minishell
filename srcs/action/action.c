/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/12 23:12:15 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error.h"

void	pipe_setting(t_forest *cur_forest)
{
	if (cur_forest->prefd > -1)
	{
		dup2(cur_forest->prefd, 0);
		close(cur_forest->prefd);
	}
	if (cur_forest->next)
	{
		dup2(cur_forest->fd[1], 1);
		close(cur_forest->fd[0]);
		close(cur_forest->fd[1]);
	}
}

void	preorder(t_info *info, t_forest *forest, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == )
}

void	fork_forest(t_info *info, t_forest *cur_forest, int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error(ERR_FORK);
	else if (pid == 0)
	{
		pipe_setting(cur_forest);
		preorder(info, cur_forest, cur_forest->root);
		exit(g_exit_status);
	}
}

void	action(t_info *info)
{
	int			in;
	int			out;
	t_forest	*cur_forest;

	cur_forest = info->forest;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	while (cur_forest)
	{
		if (cur_forest->next)
		{
			pipe(cur_forest->fd);
			cur_forest->prefd = dup(cur_forest->fd[0]);
			close(cur_forest->fd[0]);
		}
		fork_forest(info, cur_forest, in, out);
		cur_forest = cur_forest->next;
	}
}