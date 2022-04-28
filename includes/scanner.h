/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 00:45:27 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/28 22:57:12 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>
# include "env.h"
# include "tree.h"
# include "free_data.h"

/*
** =============================================================================
** scanner.c
** =============================================================================
*/
int		scan_token(t_tree *root, t_env_list *env_list);
int		iterate_scan(char **remain, int *i, t_tree *root, t_env_list *env_list);

/*
** =============================================================================
** scanner_util.c
** =============================================================================
*/
void	append_char(char *data, char **remain, int *i);
void	append_seperater(char *data, char **remain, int *i);
void	ignore_space(char *data, int *i);
void	init_str(char **str);
void	pass_sign(int type, int *i);

/*
** =============================================================================
** redirection.c
** =============================================================================
*/
int		if_red(char *data, int *i, t_tree *root, t_env_list *env_list);
int		iter_red(char *data, int *i, char **red_data, t_env_list *env_list);
int		return_red_type(char *data, int *i);
int		chk_red_err(int quot_flag, int ds_flag);

/*
** =============================================================================
** expand.c
** =============================================================================
*/
int		expand_ds(char *data, int *i, char **remain, t_env_list *env_list);
int		expand_if_match(int *i, char *key, char **remain, t_env_list *env_list);
void	no_quot_expand(char *data, int *i, char **remain, t_env_list *env_list);
void	expand_exit_status(int *i, char **res);
char	*make_key(char *data, int *i);

/*
** =============================================================================
** quot.c
** =============================================================================
*/
int		if_quot(char *data, int *i, char **remain);
int		if_quot_expand(char *data, int *i, char **remain, t_env_list *env_list);
int		find_next_dq(char *data, int *i, char **remain, t_env_list *env_list);
int		find_next_sq(char *data, int *i, char **remain);

/*
** =============================================================================
** grow.c
** =============================================================================
*/
void	grow_red(char *red_data, int type, t_tree *root);
void	grow_cmd(char *remain, t_tree *root, t_env_list *env_list);
void	parse_cmd(char *remain, char **cmds, t_env_list *env_list);
void	make_cmd(char *remain, t_env_list *env_list, char **cmd, int *i);
void	make_opts(char *remain, t_env_list *env_list, char **opts, int *i);

#endif
