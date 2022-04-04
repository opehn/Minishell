/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:24:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/04 16:55:38 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"

/* Type Definition
** =============================================================================
*/

# define LD_RED = "<<"
# define RD_RED = ">>"

typedef enum e_special 
{
	D_QUOT = '"',
	S_QUOT = '\'',
	PIPE = '|',
	LEFT_RED = '<',
	RIGHT_RED = '>',
} t_special;

typedef struct s_pipe_list
{
	int					s_idx;
	int					l_idx;
	char				*pipe_data;
	struct s_pipe_list	*next;
} t_pipe_list;

typedef struct s_node
{
	char			*left_content;
	struct s_node	*right_node;
} t_node;

typedef struct s_tree
{
	t_node			*cur;
	struct s_tree	*next;
} t_tree;

/*
** =============================================================================
** parse_chk.c
** =============================================================================
*/

void	quot_chk(int *d_quot_flag, int *s_quot_flag, char input);
int		pipe_split(char *input, t_pipe_list *temp);
int		split_if_even(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *temp);


int		parsing(char *input);
int		pipe_split(char *input, t_pipe_list *temp);
void	exit_error(char *str);
bool	is_odd(int num);
int		pipe_parsing(char *input, t_pipe_list *pipe);

t_pipe_list	*init_pipe_list(void);
void	append_pipe_list(t_pipe_list *cur, int l_idx);
bool	add_list(t_pipe_list *list, char *new_data);
int		find_char(char *input, int start);

void	ft_putendl_fd(char *s, int fd);
char	*ft_strndup(const char *s1, int n);


#endif
