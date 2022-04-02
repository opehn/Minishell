/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:24:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/03 01:16:19 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include <stdlib.h>

/* Type Definition
** =============================================================================
*/

#define	LD_RED = "<<"
#define RD_RED = ">>"

typedef enum e_special 
{
	D_QUOT = '"',
	S_QUOT = '\'',
	PIPE = '|',
	LEFT_RED = '<',
	RIGHT_RED = '>',
} t_special;

typedef struct s_node
{
	char			*node_content;
	char			*left_content;
	struct s_node	*right_node;
} t_node;

typedef struct s_cmdtree
{
	t_node	*cur;
	t_node	*next;

} t_cmdtree;

t_list	*env_list;
t_list	*cmd_list;
t_list	*pipe_list;

/*
echo	a b c "< abc|" | abc | abc
|_flag = 0 |
		1  문자
>_flag = 0 < + 토큰화
		1 문자
echo "cde"
*/
#endif
