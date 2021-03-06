/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:15:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 18:50:50 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

int	input_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (perror_redir("minishell", pathname));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	output_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (perror_redir("minishell", pathname));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	append(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (perror_redir("minishell", pathname));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	heredoc(t_info *info)
{
	int	i;

	i = 0;
	while (info->heredoc[i].index == -1)
		i++;
	if (dup2(info->heredoc[i].fd[OUT], STDIN_FILENO) == -1)
		exit_error(ERR_HEREDOC);
	info->heredoc[i].index = -1;
	close(info->heredoc[i].fd[OUT]);
	return (0);
}

int	redir_action(t_info *info, t_tree *tree)
{
	if (tree->type == INPUT_RED)
		return (input_redir(tree->data));
	else if (tree->type == OUTPUT_RED)
		return (output_redir(tree->data));
	else if (tree->type == APPEND_RED)
		return (append(tree->data));
	else if (tree->type == HEREDOC)
		return (heredoc(info));
	return (0);
}
