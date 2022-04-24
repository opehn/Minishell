/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/24 15:38:51 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "custom_cmd.h"
#include <stdio.h>

int	g_exit_status;

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


int	custom_cmd_action(t_info *info, int cmd, char **opts_arr)
{
	if (cmd == CMD_PWD)
		return (custom_pwd(opts_arr));
	else if (cmd == CMD_EXPORT)
		return (custom_export(info, opts_arr));
	else if (cmd == CMD_UNSET)
		return (custom_unset(info, opts_arr));
	else if (cmd == CMD_CD)
		return (custom_cd(info, opts_arr));
	return (0);
}

int		cmd_action(t_info *info, char *cmd, char *optarg)
{
	int		custom_cmd;
	char	*builtin_cmd_path;
	char	**opts_arr;

	custom_cmd = 0;
	custom_cmd = find_custom_cmd(cmd);
	builtin_cmd_path = find_builtin_cmd(info->env_list, cmd);

	if(custom_cmd)
	{
		opts_arr = ft_split(optarg, '\n');
		g_exit_status = custom_cmd_action(info, custom_cmd, opts_arr);
	}
	else if (builtin_cmd_path)
	{
		opts_arr = split_opts(builtin_cmd_path, optarg, SEP);
		execve(builtin_cmd_path, opts_arr, info->envp);
	}
	else
		return(ERR_CMD);
	return(0);
}

void	preorder(t_info *info, t_forest *forest, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left_child && (tree->left_child->type == INPUT_RED || tree->left_child->type == OUTPUT_RED || \
		tree->left_child->type == APPEND_RED || tree->left_child->type == HEREDOC))
	{
		if (redir_action(info, tree->left_child) != 0)
			return ;
	}
	if (tree->left_child && (tree->left_child->type == CMD))
		if (cmd_action(info, tree->left_child->data, tree->right_child->data) != 0)
			return ;
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

int	exit_status_chk(t_forest *forest)
{
	int	status;

	if (no_fork_cmd(setting_cmd(forest)))
		forest = forest->next;
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
	if (no_fork_cmd(setting_cmd(cur_forest)))
	{
		preorder(info, cur_forest, cur_forest->root);
		cur_forest = cur_forest->next;
	}
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
	}
	g_exit_status = exit_status_chk(info->forest);
}
