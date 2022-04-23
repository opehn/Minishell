/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:54:29 by acho              #+#    #+#             */
/*   Updated: 2022/04/23 19:13:52 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_same(char *opts, char c)
{
	int	cnt;

	cnt = 0;
	while (*opts)
	{
		if (*opts != c)
			cnt++;
		while (*opts && *opts != c)
		{
			opts++;
		}
		if (!*opts)
			return (cnt);
		opts++;
	}
	return (cnt);
}

static int	find_len(char *opts, char c)
{
	int		len;

	len = 0;
	while (*opts && *opts != c)
	{
		len++;
		opts++;
	}
	return (len);
}

static void	mem_free(char **array, int index)
{
	while (index--)
	{
		free(array[index]);
	}
	free(array);
}

static void	make_array(char **array,  char *cmd,  char *opts, char c, int array_len)
{
	int	cmd_len;
	int	opts_len;
	int	i;
	int	j;

	cmd_len = ft_strlen(cmd);
	array[0] = (char *)malloc(cmd_len + 1);
	array[0] = ft_strdup(cmd);
	i = 1;
	while (i < array_len)
	{
		j = 0;
		while (*opts == c)
			opts++;
		opts_len = find_len((char *)opts, c);
		array[i] = (char *)malloc(opts_len + 1);
		if (!array)
		{
			mem_free((char **)array, i);
			return ;
		}
		while (j < opts_len)
			array[i][j++] = *opts++;
		array[i][j] = 0;
		i++;
	}
	array[i] = 0;
}

char	**split_opts(char  *cmd, char  *opts, char c)
{
	int		array_len;
	char	**array;

	array_len = count_same((char *)opts, c) + 1;
	array = (char **)malloc(sizeof(char *) * (array_len + 1));
	if (!array)
		return (0);
	make_array(array, cmd, opts, c, array_len);
	return (array);
}