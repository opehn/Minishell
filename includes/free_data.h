/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:46:08 by acho              #+#    #+#             */
/*   Updated: 2022/04/28 23:46:09 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_DATA_H
# define FREE_DATA_H

# include "parsing.h"
# include <stdlib.h>

void	delete_info(t_info **info);
void	free_red_data(char *data, char **red_data, char *red);
void	free_forest(t_forest *forest);

#endif
