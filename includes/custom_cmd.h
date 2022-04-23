/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:50:39 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/23 20:42:53 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_CMD_H
# define CUSTOM_CMD_H

#include "parsing.h"

int	custom_pwd(char **optarg);
int custom_export(t_info *info, char **opts_arr);
int custom_unset(t_info *info, char **opts_arr);
#endif
