/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:27:50 by acho              #+#    #+#             */
/*   Updated: 2022/04/30 14:58:48 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

int	chk_unset_err(char **opts_arr)
{
	int	res;

	if (opts_arr[0][0] == '-')
	{
		custom_err_msg("unset", "no option", opts_arr[0]);
		ft_putendl_fd("unset : usage: unset", STDERR_FILENO);
		return (2);
	}
	res = notice_invalid_arg("unset", opts_arr);
	return (res);
}

int	unset_env(t_info *info, char **opts_arr)
{
	int			i;
	int			key_idx;
	t_env_list	*temp;
	t_env_list	*prev;

	i = 0;
	prev = info->env_list;
	key_idx = find_match_key(info->env_list, opts_arr[0]);
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
	if (!chk_unset_err(opts_arr))
		unset_env(info, opts_arr);
	return (0);
}
