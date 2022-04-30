/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:42:08 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/30 15:36:12 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

void	print_env(t_info *info)
{
	t_env_list	*env_list;

	env_list = info->env_list;
	while (env_list)
	{
		if (ft_strchr(env_list->key, '=') && env_list->value[0])
		{
			write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
			ft_putendl_fd(env_list->value, STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
}

int	custom_env(t_info *info, char **opts_arr)
{
	if (opts_arr[0])
	{
		if (opts_arr[0][0] == '-')
			custom_err_msg("env", "illegal option -- ", &opts_arr[0][1]);
		else
			custom_err_msg("env", "illegal argument -- ", &opts_arr[0][1]);
		ft_putendl_fd("unset : usage : unset", STDERR_FILENO);
		return (1);
	}
	else
		print_env(info);
	return (0);
}
