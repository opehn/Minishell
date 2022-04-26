/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:17:24 by acho              #+#    #+#             */
/*   Updated: 2022/04/26 18:49:31 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "libft.h"

void	ignore_space(char *data, int *i)
{
	if (data[*i] == ' ')
	{
		while (data[*i] == ' ')
			(*i)++;
	}
}

void	init_str(char **str)
{
	*str = malloc(1);
	*str[0] = '\0';
}

void	pass_sign(int type, int *i)
{
	if (type <= 2)
		(*i) += 1;
	else if (type <= 4)
		(*i) += 2;
}

void	append_char(char *data, char **remain, int *i)
{
	if (data[*i] && data[*i] != ' ')
	{
		*remain = ft_strjoin_ch(*remain, data[*i]);
		(*i)++;
	}
}

void	append_seperater(char *data, char **remain, int *i)
{
	if (data[*i - 1] == ' ' && (*remain)[0]
			&& (*remain)[ft_strlen(*remain) - 1] != '\n')
		*remain = ft_strjoin_ch(*remain, '\n');
}
