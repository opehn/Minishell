/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 12:22:12 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:05:09 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*point;
	int		flag;

	flag = 0;
	if (c == 0)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s != 0)
	{
		if (*s == (char)c)
		{
			point = (char *)s;
			flag = 1;
		}
		s++;
	}
	if (flag == 1)
		return (point);
	else
		return (0);
}
