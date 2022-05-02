/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:27:50 by acho              #+#    #+#             */
/*   Updated: 2022/05/02 17:12:04 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

int	unset_env(t_info *info, char *arg)
{
	int			i;
	int			key_idx;
	t_env_list	*temp;
	t_env_list	*prev;

	i = 0;
	prev = info->env_list;
	key_idx = find_match_key(info->env_list, arg);
	while (i < key_idx - 1)
	{
		prev = prev->next;
		i++;
	}
	temp = prev->next;
	prev->next = temp->next;
	free_env_node(temp);
	return (0);
}

int	custom_unset(t_info *info, char **opts_arr)
{
	int		i;
	int		res;
	char	err_arr[4];

	err_arr[0] = '-';
	err_arr[1] = '=';
	err_arr[2] = ' ';
	err_arr[3] = '\0';
	i = 0;
	if (!opts_arr[0])
		return (0);
	while (opts_arr[i])
	{
		res = 0;
		res = notice_invalid_arg("unset", err_arr, opts_arr[i]);
		if (!res)
			unset_env(info, opts_arr[i]);
		i++;
	}
	return (0);
}
