/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:22:05 by acho              #+#    #+#             */
/*   Updated: 2022/05/02 17:30:45 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "parsing.h"

extern int	g_exit_status;

int	expand_ds(char *data, int *i, char **res, t_env_list *env_list)
{
	(*i)++;
	if (data[*i] == D_QUOT || data[*i] == S_QUOT)
	{
		if_quot_expand(data, i, res, env_list);
		return (1);
	}
	else
		no_quot_expand(data, i, res, env_list);
	return (0);
}

void	no_quot_expand(char *data, int *i, char **res, t_env_list *env_list)
{
	char	*key;
	int		result;

	result = 0;
	key = make_key(data, i);
	if (key[0])
	{
		result = expand_if_match(i, key, res, env_list);
		if (!result)
			(*i) += ft_strlen(key);
	}
	else
	{
		*res = ft_strjoin_ch(*res, '$');
		(*i) += ft_strlen(key);
	}
	free (key);
}

char	*make_key(char *data, int *i)
{
	int	start;
	int	j;
	int	key_len;
	int	red_flag;

	start = *i;
	j = *i;
	key_len = 0;
	red_flag = return_red_type(data, &j);
	while (data[j] && data[j] != SEP && data[j] != S_QUOT
		&& data[j] != D_QUOT && data[j] != DS && !red_flag)
	{
		j++;
		key_len++;
		red_flag = return_red_type(data, &j);
	}
	return (ft_substr(data, start, key_len));
}

int	expand_if_match(int *i, char *key, char **res, t_env_list *env_list)
{
	char	*temp;
	int		key_len;

	if (!ft_strcmp(key, "?", ft_strlen(key), 1))
	{
		expand_exit_status(i, res);
		return (1);
	}
	while (env_list)
	{
		isequal(env_list, &key_len);
		if (!ft_strcmp(env_list->key, key,
				key_len, ft_strlen(key)))
		{
			temp = *res;
			*res = ft_strjoin_no(temp, env_list->value);
			free(temp);
			*i += key_len;
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	expand_exit_status(int *i, char **res)
{
	char	*exit_status;

	exit_status = ft_itoa(g_exit_status);
	*res = ft_strjoin(*res, exit_status);
	(*i)++;
}
