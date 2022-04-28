/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: taeheoki < taeheoki@student.42seoul.kr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/11 23:33:23 by taeheoki		  #+#	#+#			 */
/*   Updated: 2022/04/28 23:44:14 by acho             ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "action.h"
#include "free_data.h"

int	g_exit_status;

void	single_preorder(t_info *info, t_forest *cur_forest, int in, int out)
{
	preorder(info, cur_forest, cur_forest->root);
	free_forest(cur_forest);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	preorder(t_info *info, t_forest *forest, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left_child && (tree->left_child->type == INPUT_RED || \
							tree->left_child->type == OUTPUT_RED || \
							tree->left_child->type == APPEND_RED || \
							tree->left_child->type == HEREDOC))
	{
		g_exit_status = redir_action(info, tree->left_child);
		if (g_exit_status != 0)
			return ;
	}
	if (tree->left_child && (tree->left_child->type == CMD))
	{
		if (cmd_action(info, tree->left_child->data, \
							tree->right_child->data) != 0)
			return ;
	}
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
		preorder(info, cur_forest, cur_forest->root);
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

int	exit_status_chk(t_info *info)
{
	int			status;
	t_forest	*temp;
	t_forest	*temp_next;

	temp = info->forest;
	while (temp)
	{
		temp_next = temp->next;
		if (waitpid(temp->pid, &status, 0) == -1)
			exit_error(ERR_WAITPID);
		free_forest(temp);
		temp = temp_next;
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
	if (no_fork_cmd(setting_cmd(cur_forest)) && (info->pipe_cnt == 1))
		single_preorder(info, cur_forest, in, out);
	else
	{
		while (cur_forest)
		{
			if (cur_forest->next)
			{
				pipe(cur_forest->fd);
				cur_forest->next->prefd = dup(cur_forest->fd[OUT]);
				close(cur_forest->fd[OUT]);
			}
			fork_forest(info, cur_forest, in, out);
			cur_forest = cur_forest->next;
		}
		g_exit_status = exit_status_chk(info);
	}
}
