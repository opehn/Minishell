/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:04:52 by acho              #+#    #+#             */
/*   Updated: 2022/05/02 17:31:47 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

t_env_list	*sort_env_list(t_env_list *env_list)
{
	t_env_list	*cp_head;
	t_env_list	*origin_head;
	int			list_len;

	origin_head = env_list;
	list_len = 0;
	cp_head = cp_env_list(origin_head);
	while (env_list)
	{
		env_list = env_list->next;
		list_len++;
	}
	return (iter_swap(cp_head, list_len));
}

t_env_list	*iter_swap(t_env_list *cur, int list_len)
{
	t_env_list	*head;
	t_env_list	*start;
	int			i;

	head = cur;
	start = head;
	i = 0;
	while (i < list_len)
	{
		cur = start;
		while (cur->next)
		{
			if (0 < ft_strcmp(cur->key, cur->next->key, \
			ft_strlen(cur->key), ft_strlen(cur->next->key)))
				swap_data(cur);
			cur = cur->next;
		}
		i++;
		start = start->next;
	}
	return (head);
}

t_env_list	*cp_env_list(t_env_list *origin)
{
	t_env_list	*head;
	t_env_list	*temp;
	char		*cp_key;
	char		*cp_value;

	cp_key = ft_strndup(origin->key, ft_strlen(origin->key));
	cp_value = ft_strndup(origin->value, ft_strlen(origin->value));
	head = new_env_list(cp_key, cp_value);
	temp = head;
	origin = origin->next;
	while (origin)
	{
		cp_key = ft_strndup(origin->key, ft_strlen(origin->key));
		cp_value = ft_strndup(origin->value, ft_strlen(origin->value));
		temp->next = new_env_list(cp_key, cp_value);
		temp = temp->next;
		origin = origin->next;
	}
	return (head);
}

void	swap_data(t_env_list *cur)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = cur->key;
	temp_value = cur->value;
	cur->key = cur->next->key;
	cur->value = cur->next->value;
	cur->next->key = temp_key;
	cur->next->value = temp_value;
}
