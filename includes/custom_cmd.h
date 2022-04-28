/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:50:39 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/28 22:53:20 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_CMD_H
# define CUSTOM_CMD_H

# include "parsing.h"
# include "error.h"
# include "stdlib.h"
# include "env.h"
# include "libft.h"
# include <string.h>
# include <errno.h>
# include "free_data.h"

/*
** =============================================================================
** Type Definition.c
** =============================================================================
*/
typedef struct s_optarg_flag
{
	int		opt_flag;
	int		arg_flag;
}	t_optarg_flag;

/*
** =============================================================================
** custom_cd.c
** =============================================================================
*/
char		*get_env_value(t_env_list *env_list, char *key);
t_env_list	*update_env(t_env_list *env_temp, char *pwd, \
						char *oldpwd, int *flag);
void		change_env(t_info *info);
int			custom_cd(t_info *info, char **optarg);

/*
** =============================================================================
** custom_echo.c
** =============================================================================
*/
void		optarg_chk(char **optarg, t_optarg_flag *flag, int i, int j);
int			custom_echo(char **optarg);

/*
** =============================================================================
** custom_pwd.c
** =============================================================================
*/
int			update_perror(char **optarg, char *perror, int *i, int *j);
int			custom_pwd(char **optarg);

/*
** =============================================================================
** custom_env.c
** =============================================================================
*/
void		print_env(t_info *info);
int			custom_env(t_info *info, char **opts_arr);

/*
** =============================================================================
** custom_exit.c
** =============================================================================
*/
bool		isvalid_arg(char *optarg);
int			custom_exit(char **optarg);

/*
** =============================================================================
** custom_export.c
** =============================================================================
*/
int			find_equal_args(char **opts_arr);
int			chk_export_error(char **opts_arr);
void		print_env_list(t_info *info);
int			find_space(char *s);
int			custom_export(t_info *info, char **opts_arr);

/*
** =============================================================================
** custom_unset.c
** =============================================================================
*/
int			chk_unset_err(char **opts_arr);
int			unset_env(t_info *info, char **opts_arr);
int			custom_unset(t_info *info, char **opts_arr);

/*
** =============================================================================
** env_util.c
** =============================================================================
*/
t_env_list	*new_env_list(char *key, char *value);
void		append_env_list(t_info *info, char *key, char *value);
void		modify_env_list(t_info *info, char **key_value, int key_index);
int			find_match_key(t_env_list *env_list, char *key);
int			make_key_value(char *arg, char **key_value);

/*
** =============================================================================
** err_util.c
** =============================================================================
*/
void		custom_err_msg(char *func_name, char *msg, char *arg);
int			perror_cd_many(char *project, char *pathname);
int			perror_cd(char *project, char *pathname);

#endif
