/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:59:27 by acho              #+#    #+#             */
/*   Updated: 2021/05/24 11:44:44 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == ' ')
		return (1);
	return (0);
}

static int	isnum(char s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

static int	issign(char s)
{
	if (s == '+' || s == '-')
		return (1);
	return (0);
}

static long long int	calnum(char *str, int sign)
{
	long long int	num;
	int				digit;

	digit = 0;
	num = 0;
	while (isnum(*str))
	{
		num = num * 10;
		num += (*str - '0');
		str++;
		digit++;
		if (num < 0 || digit == 19)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int				sign;
	int				cnt;
	long long int	num;

	sign = 1;
	cnt = 0;
	num = 0;
	while (ft_isspace(*str))
		str++;
	while (issign(*str))
	{
		if (*str++ == '-')
			sign *= -1;
		cnt++;
	}
	if (cnt > 1)
		return (0);
	num = calnum((char *)str, sign);
	return (num * sign);
}
