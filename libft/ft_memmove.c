/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:08:28 by acho              #+#    #+#             */
/*   Updated: 2021/05/25 12:37:21 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (void *)dst;
	s = (void *)src;
	if (dst == 0 && src == 0)
		return (dst);
	while (len--)
	{
		if (dst < src)
			*d++ = *s++;
		else
			*(d + len) = *(s + len);
	}
	return ((void *)dst);
}
