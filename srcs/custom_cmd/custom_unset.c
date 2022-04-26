/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:48:59 by acho              #+#    #+#             */
/*   Updated: 2022/04/26 16:51:40 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"
#include "error.h"

#include <stdio.h>

extern int	g_exit_status;

int	chk_unset_err(char **opts_arr)
{
	int	i;

	i = 0;
	if (opts_arr[0][0] == '-') //if option
	{
		custom_err_msg("unset", "no option", NULL, 0);
		return (1);
	}
	while (opts_arr[i]) //if args has space or =
	{
		if (ft_strchr(opts_arr[i], ' ') || ft_strchr(opts_arr[i], '='))
		{
			custom_err_msg("unset", "invalid parameter name", opts_arr[0], 1);
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
	chk_unset_err(opts_arr);
	unset_env(info, opts_arr);
	return (0);
}
