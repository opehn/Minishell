/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:46:08 by acho              #+#    #+#             */
/*   Updated: 2022/04/30 14:50:48 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_DATA_H
# define FREE_DATA_H

# include "parsing.h"
# include <stdlib.h>

void	delete_info(t_info *info);
void	free_red_data(char *data, char **red_data, char *red);
void	free_forest(t_forest *forest);
void	free_env_node(t_env_list *cur);
void	free_env_list(t_env_list *env_list);
void	free_pipe(t_pipe_list *pipe);

#endif
