/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:40:26 by acho              #+#    #+#             */
/*   Updated: 2022/04/29 14:16:59 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

extern int	g_exit_status;

int	find_equal_args(char **opts_arr)
{
	int	i;

	i = 1;
	while (opts_arr[i])
	{
		if (!ft_strcmp(opts_arr[i], "=", ft_strlen(opts_arr[i]), 1))
			return (1);
		i++;
	}
	return (0);
}

int	chk_export_error(char **opts_arr)
{
	if (opts_arr[0][0] == '-')
	{
		custom_err_msg("export", "no option", NULL);
		return (2);
	}
	else if (opts_arr[1])
	{
		if (find_equal_args(opts_arr))
			custom_err_msg("export", "not a valid identifier", "=");
		return (1);
	}
	else if (find_space(opts_arr[0]))
	{
		custom_err_msg("export", "not a valid identifier", opts_arr[0]);
		return (1);
	}
	if (!ft_strchr(opts_arr[0], '='))
		return (1);
	return (0);
}

void	print_env_list(t_info *info)
{
	t_env_list	*env_list;

	env_list = info->env_list;
	while (env_list)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
		write(STDOUT_FILENO, "=", 1);
		ft_putendl_fd(env_list->value, STDOUT_FILENO);
		env_list = env_list->next;
	}
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

	if (!opts_arr[0])
	{
		print_env_list(info);
		return (0);
	}
	if (chk_export_error(opts_arr))
		return (1);
	else
	{
		make_key_value(opts_arr[0], key_value);
		match_key_index = find_match_key(info->env_list, key_value[0]);
		if (match_key_index)
			modify_env_list(info, key_value, match_key_index);
		else
			append_env_list(info, key_value[0], key_value[1]);
	}
	return (0);
}
