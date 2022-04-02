/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:58:20 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:00:28 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_set(char s1, char *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*str;
	char	*begin;
	char	*until;

	begin = (char *)s1;
	until = (char *)s1 + ft_strlen(s1);
	while (*begin && is_set(*begin, (char *)set))
		begin++;
	while (begin < until && is_set(*(until - 1), (char *)set))
		until--;
	len = until - begin;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, begin, len + 1);
	return (str);
}
