/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:14:47 by acho              #+#    #+#             */
/*   Updated: 2022/04/19 00:46:52 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	size_t			n;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) > ft_strlen(s2))
		n = ft_strlen(s1);
	else if (ft_strlen(s1) < ft_strlen(s2))
		n = ft_strlen(s2);
	else
		n = ft_strlen(s1);
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
