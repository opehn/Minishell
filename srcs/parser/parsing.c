/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:05:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/28 23:00:06 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"

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
