/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:45:42 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/03 00:03:15 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdbool.h>

void	init_list(t_list *list)
{
	s_idx = 0;
	l_idx = 0;
	list->data = NULL;
	list->next = NULL;
}

bool	add_list(t_list *list, char *new_data)
{
	char *temp;

	temp = 0;
	if (new_data == 0 || list == 0)
		return (false);
	if (list)
}
