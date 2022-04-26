/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:00 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 16:26:25 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "parsing.h"
#include "error.h"

void	quot_chk(int *d_quot_flag, int *s_quot_flag, char input)
{
	if (input == D_QUOT && !is_odd(*s_quot_flag))
		++(*d_quot_flag);
	else if (input == S_QUOT && !is_odd(*d_quot_flag))
		++(*s_quot_flag);
}

bool	is_odd(int num)
{
	if (num % 2 == 1)
		return (true);
	else
		return (false);
}

int	chk_data_null(char *input, int start, int end)
{
	int	d_quot_flag;
	int	s_quot_flag;

	while (start < end)
	{
		quot_chk(&d_quot_flag, &s_quot_flag, input[start]);
		if (!is_odd(d_quot_flag) || !is_odd(s_quot_flag))
		{
			if (input[start] != ' ')
				return (1);
		}
		start++;
	}
	return (0);
}
