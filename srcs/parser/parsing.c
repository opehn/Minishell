/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:56:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/12 17:24:27 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "error.h"
#include "parsing.h"

bool	is_odd(int num)
{
	if (num % 2 == 1)
		return (true);
	else
		return (false);
}

int		find_char(char *input, int start, int end)
{
	int i;

	i = 0;
	while(i < end && input[start] != '|')
	{
		if (input[start] != ' ')
			return (1); //if character (except space)
		start++;
		i++;
	}
	return (0);
}

/*
** =============================================================================
** pipe_parsing에 대한 의문점
** 1. ft_strlen의 경우 '\0'을 만나면 문자의 길이를 반환하는 것인데 실제로 널 위치를 반환해보면 가끔
**	  널이 아닌 경우가 있다. 하지만 길이는 항상 일정하게 나온다.
*/

int		pipe_parsing(char *input, t_pipe_list *pipe)
{
	t_pipe_list *temp;
	int			d_quot_flag;
	int			s_quot_flag;
	int			res;

	d_quot_flag = 0;
	s_quot_flag = 0;
	res = 0;
	temp = pipe;
	while (input[temp->l_idx] != '\0')
	{
		quot_chk(&d_quot_flag, &s_quot_flag, input[temp->l_idx]);
		if (input[temp->l_idx] == PIPE)
		{
			res = split_if_even(d_quot_flag, s_quot_flag, input, temp);
			temp = temp->next;
		}
		if (res)
			return (res);
		temp->l_idx++;
	}
	if (is_odd(d_quot_flag) || is_odd(s_quot_flag))
		return(ERR_UNCLOSED);
	if (temp->s_idx != temp->l_idx)
		if (find_char(input, temp->s_idx, temp->l_idx))
			pipe_split(input, temp);
	return (0);
}

int	parsing(t_info *info, char *input)
{
	t_pipe_list	*pipe;
	int	res;

	pipe = init_pipe_list();
	res = pipe_parsing(input, pipe);
	if (res)
		return (print_err(res));
	printf("파이프파싱 완료\n");
	
	parsing_tree(info, pipe);
	printf("트리 파싱 완료\n");
	
	int	i;
	int	j;
	i = 0;
	t_tree	*temp;
	while (i < count_tree(pipe))
	{
		j = 0;
		temp = info->root[i];
		while (temp->right_child)
		{
			printf("%d번째 token : %s\n", j, temp->left_child->data);
			if (!temp->right_child->right_child)
				{
					printf("cmd token : %s\n", temp->left_child->data);
					printf("optarg token : %s\n", temp->right_child->data);
				}
			temp = temp->right_child;
			j++;
		}
		i++;
	}
	//*파이프 출력 테스트*
	// int i = 0;
	// while (pipe->next)
	// {
	// 	printf("pipe[%d] : %s\n", i, pipe->pipe_data)
	// 	i++;
	// }
	free(pipe);
	pipe = 0;
	return (0);
}