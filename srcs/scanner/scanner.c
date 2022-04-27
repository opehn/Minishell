/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:14:51 by acho              #+#    #+#             */
/*   Updated: 2022/04/27 18:47:54 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "error.h"
#include "parsing.h"

int	scan_token(t_tree *root, t_env_list *env_list)
{
	int		res;
	int		i;
	char	**remain;

	if (!root->data)
		return (0);
	remain = (char **) malloc(sizeof(char *) * 1);
	if (!remain)
		exit_error(ERR_MALLOC);
	init_str(remain);
	i = 0;
	res = 0;
	res = iterate_scan(remain, &i, root, env_list);
	free(*remain);
	free(remain);
	return (res);
}

int	iterate_scan(char **remain, int *i, t_tree *root, t_env_list *env_list)
{
	int		flag;
	int		res;
	char	*data;

	flag = 0;
	res = 0;
	data = ft_strndup(root->data, ft_strlen(root->data));
	ignore_space(data, i);
	while (data[*i] && !res)
	{
		flag = *i;
		res = if_quot(data, i, remain);
		res = if_red(data, i, root, env_list);
		if (res)
			return (res);
		if (flag == *i)
		{
			append_char(data, remain, i);
			ignore_space(data, i);
			append_seperater(data, remain, i);
		}
	}
	grow_cmd(*remain, root, env_list);
	free(data);
	return (res);
}
