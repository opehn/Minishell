/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:49:56 by acho              #+#    #+#             */
/*   Updated: 2022/04/27 18:13:39 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "error.h"
#include "parsing.h"

int	if_red(char *data, int *i, t_tree *root, t_env_list *env_list)
{
	char	**red_data;
	int		type;
	int		res;

	red_data = malloc(sizeof(char *) * 1);
	init_str(red_data);
	type = return_red_type(data, i);
	if (type)
	{
		pass_sign(type, i);
		ignore_space(data, i);
		res = iter_red(data, i, red_data, env_list);
		if (res)
			return (res);
		grow_red(*red_data, type, root);
		free(*red_data);
		free(red_data);
	}
	free(*red_data);
	free(red_data);
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
	char	*substr;

	substr = ft_substr(data, *i, 2);
	if (!ft_strncmp(substr, ">>", 2))
	{
		free(substr);
		return (3);
	}
	else if (!ft_strncmp(substr, "<<", 2))
	{
		free(substr);
		return (4);
	}
	else if (data[*i] == LD)
	{
		free(substr);
		return (1);
	}
	else if (data[*i] == RD)
	{
		free(substr);
		return (2);
	}
	free(substr);
	return (0);
}
