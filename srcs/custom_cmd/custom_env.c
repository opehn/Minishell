/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:42:08 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 18:59:45 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

void	print_env(t_info *info)
{
	t_env_list	*env_list;

	env_list = info->env_list;
	while (env_list)
	{
		write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
		write(STDOUT_FILENO, "=", 1);
		ft_putendl_fd(env_list->value, STDOUT_FILENO);
		env_list = env_list->next;
	}
}

int	custom_env(t_info *info, char **opts_arr)
{
	if (opts_arr[0]) //if arg >= 1
	{
		ft_putendl_fd("minishell : env : no args or options", STDERR_FILENO);
		return (127);
	}
	else
		print_env(info);
	return (0);
}
