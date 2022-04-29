/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:02:15 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/29 17:42:10 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"
#include "action.h"

static int	perror_exit_many(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

static bool	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == ' ')
		return (true);
	return (false);
}

static bool	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool	isvalid_arg(char *optarg)
{
	int	i;

	i = 0;
	if (optarg[i])
	{
		while (ft_isspace(optarg[i]))
			++i;
		while (ft_isnum(optarg[i]))
			++i;
		while (ft_isspace(optarg[i]))
			++i;
	}
	if (optarg[i])
		return (false);
	return (true);
}

int	custom_exit(char **optarg)
{
	int	status;

	status = 0;
	if (!optarg || !(*optarg))
		exit(status);
	else if (optarg[1])
		return (perror_exit_many("minishell", "exit"));
	else if (!isvalid_arg(optarg[0]))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(perror_exit_noarg("minishell", optarg[0]));
	}
	if (optarg[0])
		status = ft_atoi(optarg[0]);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(status);
	return (0);
}
