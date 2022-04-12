#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>
# include "env.h"
# include "tree.h"

typedef enum e_token
{
    LD_RED = 1,
    RD_RED = 2,
    DQ = 3, //double quote
    SQ = 4, //single quote
	DS = 5, //dollar sign
	BS = 6, //backslash
} t_token;

bool	scan_token(t_tree *root, t_env_list *env_list);
int	    if_red(char *data, int *i, char **remain, t_tree *root);
void	if_space(char *data, int *i, char **remain);
int	    if_quote(char *data, int *i, char **remain, t_env_list *env_list);
int     find_next_dq(char *data, int *i, char **remain, t_env_list *env_list);
int	    expand_ds(char *data, int *i, char **remain, t_env_list *env_list);
int     find_next_sq(char *data, int *i, char **remain);
int	    chk_red(char *data, int *i);
void	grow_tree(char *red_data, char **remain, t_tree *root);

#endif