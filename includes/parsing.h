/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: taeheoki < taeheoki@student.42seoul.kr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/03/27 15:24:33 by taeheoki		  #+#	#+#			 */
/*   Updated: 2022/04/25 16:29:05 by acho             ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "tree.h"
# include "env.h"

/* Type Definition
** =============================================================================
*/
typedef enum e_special
{
	D_QUOT = '"',
	S_QUOT = '\'',
	PIPE = '|',
	LD = '<',
	RD = '>',
	DS = '$',
	BS = '\\',
	BT = '`',
	SEP = '\n'
} t_special;

typedef struct s_pipe_list
{
	int					s_idx;
	int					l_idx;
	char				*pipe_data;
	struct s_pipe_list	*next;
} t_pipe_list;

typedef struct s_heredoc
{
	int		fd[2];
	int		index;
} t_heredoc;

typedef struct s_info
{
	int			pipe_cnt;
	t_tree		**root;
	t_forest	*forest;
	char		**envp;
	t_env_list	*env_list;
	t_heredoc	*heredoc;
} t_info;

/*
** =============================================================================
** parsing.c
** =============================================================================
*/

int		parsing(t_info *info, char *input);

/*
** =============================================================================
** pipe_parsing_util.c
** =============================================================================
*/

bool	is_odd(int num);
void	quot_chk(int *d_quot_flag, int *s_quot_flag, char input);
int		chk_data_null(char *input, int start, int end);

/*
** =============================================================================
** pipe_parsing.c
** =============================================================================
*/

int		init_if_even(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *temp);
int		init_last(int d_quot_flag, int s_quot_flag, char *input, t_pipe_list *temp);
void	init_cur_pipe(char *input, t_pipe_list *temp);
int		pipe_parsing(char *input, t_pipe_list *pipe);

/*
** =============================================================================
** pipe_list_util.c
** =============================================================================
*/
t_pipe_list	*init_pipe_list(void);
void		append_pipe_list(t_pipe_list *cur, int l_idx);

/*
** =============================================================================
** parsing_tree.c
** =============================================================================
*/

int		parsing_tree(t_info *info, t_pipe_list *pipe);
int		count_tree(t_pipe_list *pipe);

void	exit_error(char *str);
bool		add_list(t_pipe_list *list, char *new_data);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strndup(const char *s1, int n);


#endif
