/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:47:22 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/04 19:38:33 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	print_err(int res)
{
	if (res == 1)
		ft_putendl_fd(MSG_UNCLOSED, STDERR_FILENO);
	else if (res == 2)
		ft_putendl_fd(MSG_SYNTAX, STDERR_FILENO);

	return (res);
}

void	exit_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}
