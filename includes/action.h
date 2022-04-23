#ifndef ACTION_H
# define ACTION_H

# include "parsing.h"
# include "error.h"
# include <errno.h>

# define OUT 0
# define IN 1

#define	CMD1 "echo"
#define	CMD2 "pwd"
#define	CMD3 "export"
#define	CMD4 "unset"
#define	CMD5 "exit"
/*
** =============================================================================
** action.c
** =============================================================================
*/
void	action(t_info *info);
int		exit_status_chk(t_forest *forest);
void	fork_forest(t_info *info, t_forest *cur_forest, int in, int out);
void	preorder(t_info *info, t_forest *forest, t_tree *tree);
void	pipe_setting(t_forest *cur_forest);


/*
** =============================================================================
** ft_wait.c
** =============================================================================
*/
int		ft_wifexited(int status);
int		ft_wifsignaled(int status);
int		ft_wexitstatus(int status);
int		ft_wtermsig(int status);

/*
** =============================================================================
** heredoc_chk.c
** =============================================================================
*/
void	heredoc_chk(t_info *info);
void	init_heredoc_buf(t_info *info, char *end_word, int index);
char	*line_expand(t_info *info, char *line);
int		heredoc_cnt(t_forest *forest);

/*
** =============================================================================
** redir_action.c
** =============================================================================
*/
int		redir_action(t_info *info, t_tree *tree);
int		append(char *pathname);
int		output_redir(char *pathname);
int		input_redir(char *pathname);
int		heredoc(t_info *info);
int		perror_redir(char *project, char *pathname);

/*
** =============================================================================
** find_cmd.c
** =============================================================================
*/
int     cmd_action(t_info *info, char *cmd, char *optarg);
char	*find_custom_cmd(char *cmd);
char	*find_builtin_cmd(t_env_list *env_list, char *cmd);
char    *find_env_path(t_env_list *env_list);
char    *match_builtin_cmd(char **cmd_array, char *cmd);
char	*find_custom_cmd(char *cmd);

#endif
