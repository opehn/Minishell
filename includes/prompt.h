#ifndef PROMPT_H
# define PROMPT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>

/*
** =============================================================================
** signal_handler.c
** =============================================================================
*/
void	signal_handler(int signum);
void	set_signal(void);

#endif
