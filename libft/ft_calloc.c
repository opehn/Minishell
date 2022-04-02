/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 12:15:55 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 14:19:23 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	mem_size;
	void	*ptr;
	void	*cp_ptr;

	mem_size = 0;
	mem_size += count * size;
	ptr = malloc(mem_size);
	if (!ptr)
		return (0);
	cp_ptr = ptr;
	while (mem_size--)
	{
		*(unsigned char *)cp_ptr++ = 0;
	}
	return (ptr);
}
