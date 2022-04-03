/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:56:47 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/03 08:46:59 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "prompt.h"

bool	is_odd(int num)
{
	if (num % 2 == 1)
		return (true);
	else
		return (false);
}

void	pipe_split(char *input, int start, int end, t_list *pipe)
{
	int	i;
	char	*str;

//	{ 대충 여기에 pipe.next가 NULL이 될때까지 pipe를 바꾸면됨 }
//	pipe 하나 만들고;

/*	str = (char *)malloc(sizeof(char) * (end - start));
	i = 0;
	while (start <= end)
	{
		str[i] = input[start];
		++i;
		++start;
	}
	str[i] = '\0';*/
	i = 0;
	str = NULL;
	input = 0;
	start = 0;
	end = 0;
	pipe = NULL;
}

bool	pipe_parsing(char *input, t_list *pipe)
{

	t_pipe_list	p_info;
	int	d_quot_flag;
	int	s_quot_flag;

	p_info = malloc(sizeof(t_pipe_list));
	init_list(p_info);
d_quot_flag = 0;
	s_quot_flag = 0;
	while (input[p_info.l_idx] == NULL)
	{
		if (input[p_info.l_idx] == D_QUOT)
			++d_quot_flag;
		else if (input[p_info.l_idx] == S_QUOT)
			++s_quot_flag;
		else if (input[p_info.l_idx] == PIPE)
		{
			if (!is_odd(d_quot_flag) && !is_odd(s_quot_flag))
			{
				pipe_split(input, p_info.s_idx, p_info.l_idx, pipe);
				p_info.s_idx = p_info.l_idx + 1;
			}
		}
		++(p_info.l_idx);
	}
	if (is_odd(d_quot_flag) || is_odd(s_quot_flag))
		return (false);
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

bool	parsing(char *input, t_list *env_list, t_list *cmd_list)
{
	if (pipe_parsing(input, pipe_list) == false)
		return (ERR_PARSING);
//		갯수 -> calloc 할당
	if (quoting)

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
