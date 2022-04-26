/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:47:22 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 21:52:46 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

int	print_err(int res)
{
	if (res == 1)
		ft_putendl_fd(MSG_UNCLOSED, STDERR_FILENO);
	else if (res == 2)
		ft_putendl_fd(MSG_SYNTAX, STDERR_FILENO);
	else if (res == 3)
		ft_putendl_fd(MSG_RED, STDERR_FILENO);
	else if (res == 4)
		ft_putendl_fd(MSG_CMD, STDERR_FILENO);
	else if (res == 5)
		return (5);
	return (res);
}

void	exit_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}
