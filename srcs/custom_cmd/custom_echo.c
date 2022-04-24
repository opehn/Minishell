/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:50:07 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/24 19:54:47 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

int	custom_echo(char **optarg)
{
	int		i;
	int		j;
	int		opt_flag;
	int		arg_flag;

	i = 0;
	opt_flag = 0;
	arg_flag = 0;
	while (optarg[i])
	{
		j = 0;
		if (((opt_flag == 1) && (arg_flag == 0)) || (i == 0))
		{
			if (optarg[i][j] == '-')
			{
				++j;
				while (optarg[i][j] == 'n')
					++j;
				if (optarg[i][j])
				{
					arg_flag = 1;
					ft_putstr_fd(optarg[i], STDOUT_FILENO);
				}
				else
					opt_flag = 1;
			}
			else
			{
				arg_flag = 1;
				ft_putstr_fd(optarg[i], STDOUT_FILENO);
			}
		}
		else if (arg_flag == 1)
			ft_putstr_fd(optarg[i], STDOUT_FILENO);
		++i;
		if (optarg[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (opt_flag == 0)
		ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}