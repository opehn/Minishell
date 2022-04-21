/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/21 01:10:14 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

int	g_exit_status;

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

void	preorder(t_info *info, t_forest *forest, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left_child->type == INPUT_RED || tree->left_child->type == OUTPUT_RED || \
		tree->left_child->type == APPEND_RED || tree->left_child->type == HEREDOC)
		if (redir_action(info, tree->left_child) != 0)
			return ;
	// else if (tree->left_child->type == CMD)
	// 	cmd_action(info, tree->left_child->data, tree->right_child->data);
	preorder(info, forest, tree->right_child);
}

void	fork_forest(t_info *info, t_forest *cur_forest, int in, int out)
{
	cur_forest->pid = fork();
	if (cur_forest->pid < 0)
		exit_error(ERR_FORK);
	else if (cur_forest->pid == 0)
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
		if (cur_forest->next)
		{
			close(cur_forest->fd[OUT]);
			close(cur_forest->fd[IN]);
		}
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
	}
}

int	exit_status_chk(t_forest *forest)
{
	int	status;

	while (forest)
	{
		if (waitpid(forest->pid, &status, 0) == -1)
			exit_error(ERR_WAITPID);
		forest = forest->next;
	}
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	else if (ft_wifsignaled(status))
		return (ft_wtermsig(status));
	else
		return (status % 128);
}

void	action(t_info *info)
{
	int			in;
	int			out;
	t_forest	*cur_forest;

	heredoc_chk(info);
	cur_forest = info->forest;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	while (cur_forest)
	{
		if (cur_forest->next)
		{
			pipe(cur_forest->fd);
			cur_forest->prefd = dup(cur_forest->fd[OUT]);
			close(cur_forest->fd[OUT]);
		}
		fork_forest(info, cur_forest, in, out);
		cur_forest = cur_forest->next;
	} // action 넣어서 돌려볼까? 이게 보일까?
	// 이러면 대충 보이려나?
	// 읽어줄까?
	// 나한테 관심 좀...
	// 진짜 너무한다. 이건 심하다는 생각 안들어?
	// 도대체 언제 관심 가져줄거야? 너무햇 ㅠㅠ
	g_exit_status = exit_status_chk(info->forest);
}