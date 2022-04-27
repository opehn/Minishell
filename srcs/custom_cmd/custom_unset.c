/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:27:50 by acho              #+#    #+#             */
/*   Updated: 2022/04/27 10:58:02 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

int	chk_unset_err(char **opts_arr)
{
	int	i;

	i = 0;
	if (opts_arr[0][0] == '-')
	{
		custom_err_msg("unset", "invalid option", opts_arr[0]);
		ft_putendl_fd("unset : usage: unset", STDERR_FILENO);
		return (2);
	}
	while (opts_arr[i])
	{
		if (ft_strchr(opts_arr[i], ' ') || ft_strchr(opts_arr[i], '='))
		{
			custom_err_msg("unset", "not a valid identifier", opts_arr[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_env(t_info *info, char **opts_arr)
{
	int			i;
	t_env_list	*temp;
	t_env_list	*prev;

	i = 0;
	while (opts_arr[i])
	{
		temp = info->env_list;
		prev = temp;
		while (temp)
		{
			if (!ft_strcmp(temp->key, opts_arr[i],
					ft_strlen(temp->key), ft_strlen(opts_arr[i])))
			{
				prev->next = temp->next;
				free(temp);
				break ;
			}
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return (0);
}

int	custom_unset(t_info *info, char **opts_arr)
{
	if (!chk_unset_err(opts_arr))
		unset_env(info, opts_arr);
	return (0);
}
