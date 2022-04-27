/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:05:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/27 20:08:22 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"

/*
** =============================================================================
** pipe_parsing에 대한 의문점
** 1. ft_strlen의 경우 '\0'을 만나면 문자의 길이를 반환하는 것인데 실제로 널 위치를 반환해보면 가끔
**	  널이 아닌 경우가 있다. 하지만 길이는 항상 일정하게 나온다.
*/

int	parsing(t_info *info, char *input)
{
	t_pipe_list	*pipe;
	t_pipe_list	*next;
	int			res;

	res = 0;
	if (!input[0])
		return (1);
	pipe = init_pipe_list();
	res = pipe_parsing(input, pipe);
	if (res)
		return (print_err(res));
	if (!pipe->pipe_data)
		return (0);
	res = parsing_tree(info, pipe);
	if (res)
		return (print_err(res));
	while (pipe)
	{
		next = pipe->next;
		free(pipe);
		pipe = next;
	}
	return (0);
}