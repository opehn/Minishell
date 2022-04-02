/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:30:04 by acho              #+#    #+#             */
/*   Updated: 2021/05/20 15:16:11 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_ele;

	new_ele = malloc((sizeof(t_list)) * 1);
	if (!new_ele)
		return (0);
	new_ele->content = content;
	new_ele->next = NULL;
	return (new_ele);
}
