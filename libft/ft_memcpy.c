/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:08:11 by acho              #+#    #+#             */
/*   Updated: 2021/05/24 21:47:50 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (dst);
	while (n--)
	{
		*(unsigned char *)dst++ = *(unsigned char *)src++;
		i++;
	}
	return (dst - i);
}
