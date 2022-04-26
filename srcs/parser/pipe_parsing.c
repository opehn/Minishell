/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:06:32 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 16:10:21 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "parsing.h"
#include "error.h"

int	init_if_even(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *pipe)
{
	if (!chk_data_null(input, pipe->s_idx, pipe->l_idx))
		return (ERR_SYNTAX);
	if (!is_odd(d_quot_flag) && !is_odd(s_quot_flag))
		init_cur_pipe(input, pipe);
	return (0);
}

int	init_last(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *pipe)
{
	if (is_odd(d_quot_flag) || is_odd(s_quot_flag))
		return(ERR_UNCLOSED);
	if (input[pipe->l_idx - 1] == PIPE)
		return (ERR_SYNTAX);
	if (pipe->s_idx != pipe->l_idx)
	{
		if (!chk_data_null(input, pipe->s_idx, pipe->l_idx))
			return (ERR_SYNTAX);
		init_cur_pipe(input, pipe);
	}
	return (0);
}

void	init_cur_pipe(char *input, t_pipe_list *pipe)
{
	int s_idx;
	int l_idx;

	s_idx = pipe->s_idx;
	l_idx = pipe->l_idx;
	if (!input || !pipe)
		exit_error(ERR_PIPE_SPLIT);
	pipe->pipe_data = ft_strndup(input + s_idx, l_idx - s_idx);
}

int	pipe_parsing(char *input, t_pipe_list *pipe)
{
	int	d_quot_flag;
	int	s_quot_flag;
	int	res;

	d_quot_flag = 0;
	s_quot_flag = 0;
	res = 0;
	while (input[pipe->l_idx] != '\0')
	{
		quot_chk(&d_quot_flag, &s_quot_flag, input[pipe->l_idx]);
		if (input[pipe->l_idx] == PIPE)
		{
			res = init_if_even(d_quot_flag, s_quot_flag, input, pipe);
			append_pipe_list(pipe, pipe->l_idx);
			pipe = pipe->next;
		}
		if (res)
			return (res);
		pipe->l_idx++;
	}
	return (init_last(d_quot_flag, s_quot_flag, input, pipe));
}
