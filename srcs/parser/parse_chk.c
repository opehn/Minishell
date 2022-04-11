/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:26:00 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/11 19:55:25 by taeheoki         ###   ########.fr       */
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

int	pipe_split(char *input, t_pipe_list *temp)
{
	int	s_idx;
	int	l_idx;
	int	input_len;

	s_idx = temp->s_idx;
	l_idx = temp->l_idx;
	input_len = (int)ft_strlen(input);
	if (!input || !temp)
		exit_error(ERR_PIPE_SPLIT);
	temp->pipe_data = ft_strndup(input + s_idx, l_idx - s_idx);
	if (l_idx < input_len && find_char(input, l_idx + 1, input_len))//끝이 아니면서 문자가 있을때
	{
		append_pipe_list(temp, l_idx);
		return (0);
	}
	return (ERR_SYNTAX);
}

int	split_if_even(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *temp)
{
	int	res;

	if (!is_odd(d_quot_flag) && !is_odd(s_quot_flag))
	{
		res = pipe_split(input, temp);
		if (res)
			return (res);
		// temp = temp->next;
	}
	return (0);
}


