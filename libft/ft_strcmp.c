/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:14:47 by acho              #+#    #+#             */
/*   Updated: 2022/04/23 15:08:53 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2, int s1_len, int s2_len)
{
	size_t			i;
	size_t			n;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (s1_len > s2_len)
		n = s1_len;
	else
		n = s2_len;
	while ((str1[i] != 0 && str2[i] != 0) && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i != n && str1[i] != 0)
		return (1);
	else if (i != n && str2[i] != 0)
		return (-1);
	else
		return (0);
}
