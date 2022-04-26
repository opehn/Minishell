/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:52:56 by acho              #+#    #+#             */
/*   Updated: 2022/04/26 16:52:58 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "custom_cmd.h"
#include "error.h"
#include "env.h"

extern int	g_exit_status;

void	custom_err_msg(char *func_name, char *msg, char *arg, int status)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(func_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	write(1, "\n", 1);
	g_exit_status = status;
}
