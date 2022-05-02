/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki <taeheoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:14:15 by taeheoki          #+#    #+#             */
/*   Updated: 2022/05/02 12:59:36 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_data.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*next;

	while (env_list)
	{
		next = env_list->next;
		free_env_node(env_list);
		env_list = NULL;
		env_list = next;
	}
}
