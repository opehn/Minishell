/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:43:01 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 16:43:44 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"
#include "free_data.h"

void	free_pipe_body(t_pipe_list *pipe)
{
	t_pipe_list	*next;

	next = NULL;
	while (pipe)
	{
		next = pipe->next;
		free(pipe);
		pipe = next;
	}
}

int	parsing(t_info *info, char *input)
{
	t_pipe_list	*pipe;
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
		free_pipe_body(pipe);
		return (print_err(res));
	}
	free_pipe_body(pipe);
	return (0);
}
