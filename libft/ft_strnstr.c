/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:43:00 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:10:03 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;
	char	*cp_nd;

	cnt = 0;
	cp_nd = (char *)needle;
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack++ != 0 && len > 0)
	{
		while (*(haystack - 1) == *cp_nd && len > 0)
		{
			haystack++;
			cp_nd++;
			cnt++;
			len--;
			if (*cp_nd == 0)
				return ((char *)haystack - cnt - 1);
		}
		cp_nd = (char *)needle;
		haystack -= cnt;
		len += cnt;
		len--;
		cnt = 0;
	}
	return (NULL);
}
