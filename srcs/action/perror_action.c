/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:32:08 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 13:32:28 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

int	perror_redir(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}
