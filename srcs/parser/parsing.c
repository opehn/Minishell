/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:05:23 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 16:27:44 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"
#include "free_data.h"
#include <stdio.h>

char	*test_type(int	type)
{
	if (type == 1)
		return ("INPUT_RED");
	else if (type == 2)
		return ("OUTPUT_RED");
	else if (type == 3)
		return ("APPEND_RED");
	else if (type == 4)
		return ("HEREDOC");
	else if (type == 5)
		return ("CMD");
	else if (type == 6)
		return ("OPTARG");
	else if (type == 7)
		return ("BRANCH");
	return (NULL);
}

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

int	i;
	int	j;
	i = 0;
	t_tree	*temp;
	while (i < count_tree(pipe))
	{
		j = 0;
		temp = info->root[i];
		printf("---------%d 번째 파이프 ------------\n", i);
		while (temp->right_child)
		{
			if (!temp->right_child->right_child)
			{
				printf("%s \t\t\ttoken : %s\n", test_type(temp->left_child->type), temp->left_child->data);
				printf("%s \t\t\ttoken : %s\n", test_type(temp->right_child->type), temp->right_child->data);
				break;
			}
			else
				printf("%s \t\ttoken : %s\n", test_type(temp->left_child->type), temp->left_child->data);
			temp = temp->right_child;
			j++;
		}
		i++;
	}

	if (res)
	{
		free_pipe_body(pipe);
		return (print_err(res));
	}
	free_pipe_body(pipe);
	return (0);
}
