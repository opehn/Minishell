/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:15:35 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/30 17:56:35 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

extern int	g_exit_status;

int	chk_export_error(char **opts_arr)
{
	int		i;
	int		res;
	char	err_arr[2];

	i = 0;
	if (opts_arr[0][0] == '-')
	{
		custom_err_msg("export", "no option", NULL);
		ft_putendl_fd("export : usage: export", STDERR_FILENO);
		return (1);
	}
	while (opts_arr[i])
	{
		if (opts_arr[i][0] == '=')
			custom_err_msg("export", "not a valid identifier", opts_arr[i]);
		i++;
	}
	err_arr[0] = ' ';
	err_arr[1] = '-';
	res = notice_invalid_arg("export", err_arr, opts_arr);
	return (res);
}

int	print_env_export(t_env_list *env_list)
{
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
	free_env_list(env_list);
	return (0);
}

int	find_space(char *s)
{
	while (*s)
	{
		if (*s == ' ')
			return (1);
		s++;
	}
	return (0);
}

int	custom_export(t_info *info, char **opts_arr)
{
	char	*key_value[2];
	int		match_key_index;
	int		i;

	i = 0;
	if (!opts_arr[0])
		return (print_env_export(sort_env_list(info->env_list)));
	if (chk_export_error(opts_arr))
		return (1);
	else
	{
		while (opts_arr[i])
		{
			make_key_value(opts_arr[i], key_value);
			match_key_index = find_match_key(info->env_list, key_value[0]);
			if (match_key_index >= 0)
				modify_env_list(info, key_value, match_key_index);
			else
				append_env_list(info, key_value[0], key_value[1]);
			i++;
		}
	}
	return (0);
}
