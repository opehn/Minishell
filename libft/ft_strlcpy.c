/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 12:21:09 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:04:05 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = 0;
	dstlen = 0;
	i = 0;
	while (src[srclen])
		srclen++;
	if (len == 0)
		return (srclen);
	while (dst[dstlen])
		dstlen++;
	while (len-- - 1 > 0 && *src != 0)
	{
		dst[i++] = *src++;
	}
	dst[i] = 0;
	return (srclen);
}
