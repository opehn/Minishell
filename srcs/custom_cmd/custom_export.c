/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:15:35 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 17:57:37 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"
#include <stdio.h>

extern int	g_exit_status;

void	make_err_arr(char	*err_arr)
{
	err_arr[0] = ' ';
	err_arr[1] = '-';
	err_arr[2] = '\0';
}

int	chk_export_error(t_info *info, char **opts_arr)
{
	int		i;
	int		flag;
	int		res;
	char	err_arr[3];

	make_err_arr(err_arr);
	i = -1;
	flag = 0;
	while (opts_arr[++i])
	{
		res = 0;
		res = notice_invalid_arg("export", err_arr, opts_arr[i]);
		if (res)
			flag = res;
		if (opts_arr[i][0] == '=')
		{
			res = custom_err_msg("export", "not a valid identifier",
					opts_arr[i]);
			flag = res;
		}
		if (!res)
			append_export(info, opts_arr[i]);
	}
	return (flag);
}

int	print_env_export(t_env_list *env_list)
{
	t_env_list	*head;

	head = env_list;
	while (env_list)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
		if (ft_strchr(env_list->key, '='))
			write(STDOUT_FILENO, "\"", 1);
		ft_putstr_fd(env_list->value, STDOUT_FILENO);
		if (ft_strchr(env_list->key, '='))
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		env_list = env_list->next;
	}
	free_env_list(head);
	return (0);
}

void	append_export(t_info *info, char *arg)
{
	int		match_key_index;
	char	*key_value[2];

	make_key_value(arg, key_value);
	match_key_index = find_match_key(info->env_list, key_value[0]);
	if (match_key_index >= 0)
		modify_env_list(info, key_value, match_key_index);
	else
		append_env_list(info, key_value[0], key_value[1]);
}

int	custom_export(t_info *info, char **opts_arr)
{
	if (!opts_arr[0])
		return (print_env_export(sort_env_list(info->env_list)));
	return (chk_export_error(info, opts_arr));
}
