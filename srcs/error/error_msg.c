/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:47:22 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/27 11:02:35 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

extern int	g_exit_status;

int	print_err(int res)
{
	if (res == 1)
	{
		g_exit_status = 1;
		ft_putendl_fd(MSG_UNCLOSED, STDERR_FILENO);
	}
	else if (res == 2)
	{
		g_exit_status = 2;
		ft_putendl_fd(MSG_SYNTAX, STDERR_FILENO);
	}
	else if (res == 3)
	{
		g_exit_status = 1;
		ft_putendl_fd(MSG_RED, STDERR_FILENO);
	}
	else if (res == 4)
	{
		g_exit_status = 127;
		ft_putendl_fd(MSG_CMD, STDERR_FILENO);
	}
	else if (res == 5)
		return (5);
	return (res);
}

void	exit_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}
