/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:05:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/29 16:21:32 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"
#include "free_data.h"

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
	{		
		free_pipe(pipe);
		return (print_err(res));
	}
	if (!pipe->pipe_data)
		return (0);
	res = parsing_tree(info, pipe);
	if (res)
	{
		while (pipe)
		{
			next = pipe->next;
			free(pipe);
			pipe = next;
		}
		return (print_err(res));
	}
	while (pipe)
	{
		next = pipe->next;
		free(pipe);
		pipe = next;
	}
	return (0);
}
