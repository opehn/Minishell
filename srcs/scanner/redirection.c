/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:49:56 by acho              #+#    #+#             */
/*   Updated: 2022/04/26 15:17:16 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

int	if_red(char *data, int *i, t_tree *root, t_env_list *env_list)
{
	char	**red_data;
	int		type;
	int		res;

	red_data = malloc(sizeof(char *) * 1);
	init_str(red_data);
	type = return_red_type(data, i); //check red type
	if (type)
	{
		pass_sign(type, i); //move idx of data to file name
		ignore_space(data, i);
		res = iter_red(data, i, red_data, env_list);
		if (res)
			return (res);
		grow_red(*red_data, type, root);
	}
	return (0);
}

int	iter_red(char *data, int *i, char **red_data, t_env_list *env_list)
{
	int	quot_flag;
	int	ds_flag;
	int	start;

	quot_flag = 0;
	ds_flag = 0;
	start = *i;
	while (!return_red_type(data, i) && data[*i] != ' ' && data[*i])
	{
		start = *i;
		quot_flag = if_quot_expand(data, i, red_data, env_list);
		if (data[*i] == DS)
		{
			ds_flag = 1;
			quot_flag = expand_ds(data, i, red_data, env_list);
		}
		if (start == *i)
		{
			*red_data = ft_strjoin_ch(*red_data, data[*i]);
			(*i)++;
		}
	}
	if (!*red_data[0])
		return (chk_red_err(quot_flag, ds_flag));
	return (0);
}

int	chk_red_err(int quot_flag, int ds_flag)
{
	if (!quot_flag && !ds_flag)
		return (ERR_SYNTAX);
	else if (!quot_flag && ds_flag)
		return (ERR_RED);
	else
		return (0);
}

int	return_red_type(char *data, int *i)
{
	if (!ft_strncmp(ft_substr(data, *i, 2), ">>", 2))
		return (3);
	else if (!ft_strncmp(ft_substr(data, *i, 2), "<<", 2))
		return (4);
	else if (data[*i] == LD)
		return (1);
	else if (data[*i] == RD)
		return (2);
	return (0);
}
