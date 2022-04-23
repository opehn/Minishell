/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:05:56 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/22 17:46:39 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"
#include "error.h"
#include "stdlib.h"

extern int	g_exit_status;

static int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == ' ')
		return (1);
	return (0);
}

int	custom_pwd(char **optarg)
{
	char	*path;
	char	*perror;
	int		i;
	int		j;

	perror = NULL;
	i = 0;
	while (optarg[i])
	{
		j = 0;
		if (optarg[i][j] == '-')
		{
			++j;
			if ((optarg[i][j] != '\0') || optarg[i][j] != '-')
			{
				perror = ft_strjoin_ch(ft_strjoin_ch("minishell: pwd : -", &optarg[i][j]),\
						": invalid option\n pwd: usage: pwd");
				ft_putendl_fd(perror, 2);
				free(perror);
				perror = 0;
				return (2);
			}
			if (optarg[i][j] == '-')
			{
				++j;
				if (optarg[i][j] != '\0')
				{
					perror = "minishell: pwd : --: invalid option\n pwd: usage: pwd";
					ft_putendl_fd(perror, 2);
					return (2);
				}
			}
		}
		++i;
	}
	path = getcwd(NULL, 0);
	if (!path)
		exit_error(ERR_MALLOC);
	ft_putendl_fd(path, 1);
	free(path);
	path = 0;
	return (0);
}