/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:50:39 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/25 00:04:06 by acho             ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef CUSTOM_CMD_H
# define CUSTOM_CMD_H

# include "parsing.h"
# include "error.h"
# include "stdlib.h"
# include "env.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>

int custom_pwd(char **optarg);

char    *get_env_value(t_env_list *env_list, char *key);
void    change_env(t_info *info);
int     custom_cd(t_info *info, char **optarg);

int custom_export(t_info *info, char **opts_arr);
int custom_unset(t_info *info, char **opts_arr);

int    find_match_key(t_env_list *env_list, char *key);
void    append_env_list(t_info *info, char *key, char *value);
t_env_list  *new_env_list(char *key, char *value);
int make_key_value(char *arg, char **key_value);
int  find_space(char *s);
void    modify_env_list(t_info *info, char **key_value, int key_index);
int custom_echo(char **optarg);

#endif 
