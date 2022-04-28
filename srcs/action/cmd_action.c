/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:42:50 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/28 18:39:55 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "action.h"
#include "custom_cmd.h"

extern int	g_exit_status;

int	custom_cmd_action(t_info *info, int cmd, char **opts_arr)
{
	if (cmd == CMD_PWD)
		return (custom_pwd(opts_arr));
	else if (cmd == CMD_EXPORT)
		return (custom_export(info, opts_arr));
	else if (cmd == CMD_UNSET)
		return (custom_unset(info, opts_arr));
	else if (cmd == CMD_CD)
		return (custom_cd(info, opts_arr));
	else if (cmd == CMD_ECHO)
		return (custom_echo(opts_arr));
	else if (cmd == CMD_EXIT)
		return (custom_exit(opts_arr));
	else if (cmd == CMD_ENV)
		return (custom_env(info, opts_arr));
	return (0);
}

static int	perror_cmd(char *project, char *cmd)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
	return (127);
}

void	free_cmd_all(char **opts_arr, char *builtin_cmd_path)
{
	int	i;

	if (builtin_cmd_path)
		free(builtin_cmd_path);
	if (opts_arr)
	{	
		i = 0;
		while((opts_arr)[i])
		{
			free((opts_arr)[i]);
			i++;
		}
		free(opts_arr);
	}
}

int	cmd_action(t_info *info, char *cmd, char *optarg)
{
	int		custom_cmd;
	char	*builtin_cmd_path;
	char	**opts_arr;

	if (!cmd[0])
		return (0);
	custom_cmd = find_custom_cmd(cmd);
	builtin_cmd_path = find_builtin_cmd(info->env_list, cmd);
	if (custom_cmd)
	{
		opts_arr = ft_split(optarg, '\n');
		g_exit_status = custom_cmd_action(info, custom_cmd, opts_arr);
	}
	else if (builtin_cmd_path)
	{
		opts_arr = split_opts(builtin_cmd_path, optarg, SEP);
		execve(builtin_cmd_path, opts_arr, info->envp);
	}
	else
	{
		opts_arr = split_opts(cmd, optarg, SEP);
		execve(cmd, opts_arr, info->envp);
		g_exit_status = perror_cmd("minishell", cmd);
	}
	free_cmd_all(opts_arr, builtin_cmd_path);
	return (0);
}
