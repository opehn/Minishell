/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:15:35 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 13:51:51 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

extern int	g_exit_status;

int	chk_export_error(t_info *info, char **opts_arr)
{
	int		i;
	int		flag;
	int		res;
	char	err_arr[3];

	err_arr[0] = ' ';
	err_arr[1] = '-';
	err_arr[2] = '\0';
	i = 0;
	flag = 0;
	while (opts_arr[i])
	{
		res = 0;
		res = notice_invalid_arg("export", err_arr, opts_arr[i]);
		flag = res;
		if (opts_arr[i][0] == '=')
		{
			custom_err_msg("export", "not a valid identifier", opts_arr[i]);
			res = 2;
			flag = res;
		}
		if (!res)
			append_export(info, opts_arr[i]);
		i++;
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
