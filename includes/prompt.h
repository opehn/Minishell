#ifndef PROMPT_H
# define PROMPT_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

//p_info

typedef struct s_pipe_list
{
	int	s_idx;
	int	l_idx;
	char	*pipe_data;
	struct s_pipe_list	*next;
} t_pipe_list;

#endif
