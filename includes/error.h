#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

//===========================exit error=====================================//
# define ERR_PIPE_SPLIT "Failure to split pipe"
# define ERR_PARSING "Failure to parse"
# define ERR_MALLOC "Failure to allocate memory"
# define ERR_NULL 	"NULL"
# define ERR_TOKENIZE "Failure to tokenize pipe_data"
# define ERR_FORK "Faulure to fork"

// ========================non-exit error===================================//
# define ERR_UNCLOSED 1
# define ERR_SYNTAX 2

# define MSG_UNCLOSED "Unclosed sequence detected"
# define MSG_SYNTAX "Syntex error"

/*
** =============================================================================
** error_msg.c
** =============================================================================
*/

int		print_err(int res);
void	exit_error(char *str);


#endif



