/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:56:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/03 22:21:14 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "parsing.h"
#include "error.h"

void	exit_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

bool	is_odd(int num)
{
	if (num % 2 == 1)
		return (true);
	else
		return (false);
}

int		find_char(char *input, int start)
{
	while(input[start] && input[start] != '|')
	{
		if (input[start] != ' ')
			return (1);
		start++;
	}
	return (0);
}

int	pipe_split(char *input, t_pipe_list *temp)
{
	int	s_idx;
	int	l_idx;

	s_idx = temp->s_idx;
	l_idx = temp->l_idx;
	if (!input || !temp)
		exit_error(ERR_PIPE_SPLIT);
	temp->pipe_data = ft_strndup(input + s_idx, l_idx - s_idx);
	printf("next char : %c %d\n", input[l_idx + 1], (int)input[l_idx + 1]);
	if (find_char(input, l_idx + 1) && l_idx < (int)ft_strlen(input))
	{
		append_pipe_list(temp, l_idx);
		return (0);
	}
	return (ERR_SYNTAX);
}

// void	is_blank(char *input, int l_idx)
// {
// 	if(input )
// }

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
		if (input[temp->l_idx] == D_QUOT && !is_odd(s_quot_flag))
			++d_quot_flag;
		else if (input[temp->l_idx] == S_QUOT && !is_odd(d_quot_flag))
			++s_quot_flag;
		else if (input[temp->l_idx] == PIPE)
		{
			if (!is_odd(d_quot_flag) && !is_odd(s_quot_flag))
			{
				res = pipe_split(input, temp);
				if (res)
					return (res);
				temp = temp->next;
			}
		}
		temp->l_idx++;
	}
	if (is_odd(d_quot_flag) || is_odd(s_quot_flag))
			return(ERR_UNCLOSED);
	if (temp->s_idx != temp->l_idx)
		if (find_char(input, temp->s_idx))
			pipe_split(input, temp);
	return (0);
}

// bool	quoting(char *input)
// {
// 	while (input)
// 	{
		
// 		if (input == S_QUOT)
// 		{
			

// 		}
// 		else if (input == D_QUOT)
// 	}
// }

int	parsing(char *input)// t_list *env_list, t_list *cmd_list)
{
	t_pipe_list	*pipe;
	int	res;

	pipe = init_pipe_list();
	res = pipe_parsing(input, pipe);
	if (res)
	{
		printf("res : %d in parsing\n", res);
		return (res);
	}


	
//		갯수 -> calloc 할당
//	if (quoting)
	free(pipe);
	pipe = 0;
	return (0);
}



// $PATH = /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/opt/homebrew/bin:/opt/homebrew/sbin

// 1. 입력을 받는다
// 2. 큰따옴표 작은 따옴표 짝을 맞춘다
// 	- 홀수면 무조건 에러               => 우리만의 규칙
// 3. 0 : 특별한 의미 고려
//    2이상 : 그대로 
// 		  quoting의 시작 인덱스와 마지막 인덱스 사이의 문자는 무시
// 		  quoting된 문자열 전체를 잘라서 저장
// 		  -> 출력할때 넣어야 됨. 어디에 넣을지 어떻게 판단?이 궁금
// 		  echo "a    b     c" a  b c "c d e |" | abc | abc
// 		 1. "a    b     c"
// 		 2. "c d e |"
//  |_flag = 1, 3, 5 ,7
//  |_flag = 2, 4, 6 ,8
//  		 echo a b c | abc | a	
// 		str

// '$ABC'
// "$ABC"

// $ABC = "abc";

// 홀수 => 종료
// 짝수 => 짝수 따옴표 있을 때 짝수 따옴표로 묶인거 str + 뒤에 붙어 있는거까지 strjoin

// if (paring != 0)
// 	return (ERR_NUMBER);

// if (paring != 0)
// 	return (ERR_NUMBER);

// if (paring != 0)
// 	return (ERR_NUMBER);

// return (parsing(a, b, c));