/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/14 16:26:18 by taeheoki         ###   ########.fr       */
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
	if (tree->type == INPUT_RED || tree->type == OUTPUT_RED || \
		tree->type == APPEND_RED || tree->type == HEREDOC)
		redir_action(info, forest, tree);
	else if (tree->type == CMD)
		cmd_action(info, tree->data);
	preorder(info, forest, tree->left_child);
	preorder(info, forest, tree->right_child);
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
		while (cur_forest)
		{
			preorder(info, cur_forest, cur_forest->root);
			cur_forest = cur_forest->next;
		}
		exit(g_exit_status);
	}
	else
	{
		if (cur->cur_forest->next)
		{
			close(cur_forest->fd[0]);
			close(cur_forest->fd[1]);
		}
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
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