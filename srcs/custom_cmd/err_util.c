/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:19:22 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 17:51:19 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

extern int	g_exit_status;

int	custom_err_msg(char *func_name, char *msg, char *arg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(func_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	write(1, "\n", 1);
	return (1);
}

int	notice_invalid_arg(char *func, char *err_arr, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
	{
		custom_err_msg(func, "no option", arg);
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, " : usage: ", 10);
		write(STDERR_FILENO, func, ft_strlen(func));
		write(STDERR_FILENO, "\n", 1);
		return (2);
	}
	while (err_arr[i])
	{
		if (ft_strchr(arg, err_arr[i]))
		{
			custom_err_msg(func, "not a valid identifier", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	perror_cd_many(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	perror_cd(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}
