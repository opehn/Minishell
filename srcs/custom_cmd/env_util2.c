/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:04:52 by acho              #+#    #+#             */
/*   Updated: 2022/04/30 16:05:21 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

t_env_list	*sort_env_list(t_env_list *env_list)
{
	t_env_list	*cp;
	t_env_list	*head;
	int			list_len;
	head = env_list;
	list_len = 0;
	while (env_list)
	{
		env_list = env_list->next;
		list_len++;
	}
	cp = cp_env_list(head);
	return (iter_swap(cp, list_len));
}

t_env_list	*iter_swap(t_env_list *cur, int	list_len)
{
	t_env_list *head;
	int			i;
	int			j;
	head = cur;
	i = 0;
	j = 0;
	while (i < list_len)
	{
		cur = head;
		while (cur->next)
		{
			if (cur->key[0] > cur->next->key[0])
				swap_data(cur);
			cur = cur->next;
		}
		i++;
		while (j < i)
		{
			cur = head->next;
			j++;
		}
		j = 0;
	}
	return (head);
}

t_env_list	*cp_env_list(t_env_list *origin)
{
	t_env_list *head;
	t_env_list *temp;

	head = (t_env_list *)malloc (sizeof(t_env_list));
	temp = head;
	temp->key = ft_strndup(origin->key, ft_strlen(origin->key));
	temp->value = ft_strndup(origin->value, ft_strlen(origin->value));
	while (origin->next)
	{
		temp->next = new_env_list(origin->next->key, origin->next->value);
		temp = temp->next;
		origin = origin->next;
	}
	temp = new_env_list(origin->key, origin->value);
	temp->next = NULL;
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
