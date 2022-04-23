/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:50:39 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/23 23:37:24 by taeheoki         ###   ########.fr       */
/*                                                                            */
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

int	custom_pwd(char **optarg);

char	*get_env_value(t_env_list *env_list, char *key);
void	change_env(t_info *info);
int		custom_cd(t_info *info, char **optarg);

int custom_export(t_info *info, char **opts_arr);
int custom_unset(t_info *info, char **opts_arr);

#endif