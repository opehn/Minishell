#ifndef ACTION_H
# define ACTION_H

# include "parsing.h"
# include "error.h"
# include <errno.h>
# include <string.h>

# define OUT 0
# define IN 1

typedef enum e_custom_cmd
{
	CMD_ECHO = 2,
	CMD_CD = 3,
	CMD_PWD = 4,
	CMD_EXPORT = 5,
	CMD_UNSET = 6,
	CMD_EXIT = 7,
	CMD_ENV = 8,
} t_custom_cmd;
/*
** =============================================================================
** action.c
** =============================================================================
*/
void	single_preorder(t_info *info, t_forest *cur_forest, int in, int out);
void	preorder(t_info *info, t_forest *forest, t_tree *tree);
void	fork_forest(t_info *info, t_forest *cur_forest, int in, int out);
int		exit_status_chk(t_info *info);
void	action(t_info *info);

/*
** =============================================================================
** cmd_action.c
** =============================================================================
*/
int		custom_cmd_action(t_info *info, int cmd, char **opts_arr);
int		cmd_action(t_info *info, char *cmd, char *optarg);

/*
** =============================================================================
** action_utils.c
** =============================================================================
*/
char	*setting_cmd(t_forest *forest);
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
int		heredoc_setting(t_info *info, t_forest	*cur_forest, int index);
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

/*
** =============================================================================
** find_cmd.c
** =============================================================================
*/
char	*find_builtin_cmd(t_env_list *env_list, char *cmd);
char    *find_env_path(t_env_list *env_list);
char    *match_builtin_cmd(char **cmd_array, char *cmd);
int		find_custom_cmd(char *cmd);
int		no_fork_cmd(char *cmd);

char    **split_opts(char const *cmd, char const *opts, char c);

/*
** =============================================================================
** find_cmd.c
** =============================================================================
*/
int		perror_redir(char *project, char *pathname);
int		perror_exit_noarg(char *project, char *pathname);

#endif
