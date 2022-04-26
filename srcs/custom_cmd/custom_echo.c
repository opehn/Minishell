/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:50:07 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/27 00:25:01 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

void	optarg_chk(char **optarg, t_optarg_flag *flag, int i, int j)
{
	if (optarg[i][j] == '-')
	{
		++j;
		if (!optarg[i][j])
		{
			ft_putstr_fd("-", STDOUT_FILENO);
			return ;
		}
		while (optarg[i][j] == 'n')
			++j;
		if (optarg[i][j])
		{
			flag->arg_flag = 1;
			ft_putstr_fd(optarg[i], STDOUT_FILENO);
		}
		else
			flag->opt_flag = 1;
	}
	else
	{
		flag->arg_flag = 1;
		ft_putstr_fd(optarg[i], STDOUT_FILENO);
	}
}

int	custom_echo(char **optarg)
{
	int				i;
	int				j;
	t_optarg_flag	flag;

	i = 0;
	flag = (t_optarg_flag){0, };
	while (optarg[i])
	{
		j = 0;
		if (((flag.opt_flag == 1) && (flag.arg_flag == 0)) || (i == 0))
			optarg_chk(optarg, &flag, i, j);
		else if (flag.arg_flag == 1)
			ft_putstr_fd(optarg[i], STDOUT_FILENO);
		++i;
		if (optarg[i] && (flag.arg_flag == 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (flag.opt_flag == 0)
		ft_putendl_fd("", STDOUT_FILENO);
	return (0);
}
