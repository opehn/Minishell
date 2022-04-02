/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:52:08 by acho              #+#    #+#             */
/*   Updated: 2021/05/19 17:07:14 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	recur(int n, int fd)
{
	char	a;

	if (n == 0)
		return ;
	recur(n / 10, fd);
	a = n % 10 + '0';
	write(fd, &a, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	a;

	if (n < 0)
	{
		a = (n % 10) * -1 + '0';
		if (n > -10)
			write(fd, "-", 1);
	}
	else
		a = n % 10 + '0';
	n /= 10;
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	recur(n, fd);
	write(fd, &a, 1);
}
