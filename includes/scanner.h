#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>
# include "env.h"
# include "tree.h"

int		scan_token(t_tree *root, t_env_list *env_list);
int     if_red(char *data, int *i, char **remain, t_tree *root, t_env_list *env_list);
void    ignore_space(char *data, int *i);
int     if_quot(char *data, int *i, char **remain);
int     if_quot_expand(char *data, int *i, char **remain, t_env_list *env_list);
int     find_next_dq(char *data, int *i, char **remain, t_env_list *env_list);
int     expand_ds(char *data, int *i, char **remain, t_env_list *env_list, int quot_flag);
int     find_next_sq(char *data, int *i, char **remain);
int     chk_red(char *data, int *i);
void    grow_tree(char *red_data, char *remain, t_tree *root, int res, t_env_list *env_list);
void    parse_cmd(char *remain, char **cmds, t_env_list *env_list);
void    init_str(char **str);
int     expand_if_match(char *data, int *i, char *key, char **remain, t_env_list *env_list);
int     iterate_scan(char *data, char **remain, int *i, t_tree *root, t_env_list *env_list);
char	*make_key(char *data, int *i, int quot_flag);
void	pass_bs(char *data, int *i, char **remain);
#endif
