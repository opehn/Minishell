/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2022/03/27 14:56:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/23 23:55:19 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"

char	*test_type(int	type);

/*
** =============================================================================
** pipe_parsing에 대한 의문점
** 1. ft_strlen의 경우 '\0'을 만나면 문자의 길이를 반환하는 것인데 실제로 널 위치를 반환해보면 가끔
**	  널이 아닌 경우가 있다. 하지만 길이는 항상 일정하게 나온다.
*/

int	parsing(t_info *info, char *input)
{
	t_pipe_list	*pipe;
	int	res;

	res = 0;
	if (!input[0])
		return (1);
	pipe = init_pipe_list();
	res = pipe_parsing(input, pipe);
	if (res)
		return (print_err(res));
	if (!pipe->pipe_data)
		return (0);
	//printf("파이프파싱 완료\n");
	
	res = parsing_tree(info, pipe);
	if (res)
		return (print_err(res));
//	printf("트리 파싱 완료\n");
	
/*	   int	i;
	   int	j;
	   i = 0;
	   t_tree	*temp;
	   while (i < count_tree(pipe))
	   {
	   	j = 0;
	   	temp = info->root[i];
	   	printf("---------%d 번째 파이프 ------------\n", i);
	   	printf("root_data : %s\n", info->root[i]->data);
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
	   }*/
	free(pipe);
	pipe = 0;
	return (0);
}

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
