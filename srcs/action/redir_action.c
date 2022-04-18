/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:15:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/18 20:12:38 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

int	perror_redir(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("pathname ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

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
	dup2(fd , STDOUT_FILENO);
	close(fd);
	return (0);
}

int append(char *pathname)
{
	int	fd;

	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (perror_redir("minishell", pathname));
	dup2(fd , STDOUT_FILENO);
	close(fd);
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
		return (heredoc(info, tree->data));
	return (0);
}

// void	cmd_action(info, tree->data)
// {
	
// }
