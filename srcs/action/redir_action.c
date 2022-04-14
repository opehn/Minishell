/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:15:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/14 23:28:37 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

bool	perror_redir(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("pathname ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	
	return (false);
}

bool 	input_redir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY)
	if (fd == -1)
		return (perror_redir("minishell", pathname));
	
}

bool	redir_action(t_info *info, t_tree *tree)
{
	if (tree->type == INPUT_RED)
		return (input_redir(tree->data));
	else if (tree->type == OUTPUT_RED)
		return (output_redir(tree->data));
	else if (tree->type == APPEND_RED)
		return (append(tree->data));
	else if (tree->type == HEREDOC)
		return ;
		// heredoc()
	return ;
}

// void	cmd_action(info, tree->data)
// {
	
// }
