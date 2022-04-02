/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:15:31 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:11:46 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}

static void	check_minus(int n, int *len, int *sign)
{
	if (n < 0)
	{
		*len += 1;
		*sign = -1;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	int		i;
	char	*res;

	sign = 1;
	len = count_digit(n);
	check_minus(n, &len, &sign);
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	res[len - 1] = n % 10 * sign + '0';
	n = n / 10 * sign;
	i = len - 2;
	while (n)
	{
		res[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}
