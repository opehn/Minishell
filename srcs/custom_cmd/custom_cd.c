/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:15:27 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/23 23:04:24 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

static int	perror_cd_many(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

static int	perror_cd(char *project, char *pathname)
{
	ft_putstr_fd(project, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

char	*get_env_value(t_env_list *env_list, char *key)
{
	t_env_list	*env_temp;

	env_temp = env_list;
	while (env_temp)
	{
		if (!ft_strcmp(env_temp->key, key, ft_strlen(env_temp->key), ft_strlen(key)))
			return (ft_strdup(env_temp->value));
		env_temp = env_temp->next;
	}
	return (NULL);
}

void	change_env(t_info *info)
{
	char		*pwd;
	char		*oldpwd;
	t_env_list	*env_temp;
	
	env_temp = info->env_list;
	pwd = getcwd(NULL, 0);
	oldpwd = get_env_value(info->env_list, "PWD");
	while (env_temp)
	{
		if (!ft_strcmp(env_temp->key, "PWD", ft_strlen(env_temp->key), ft_strlen("PWD")))
		{
			free(env_temp->value);
			env_temp->value = pwd;
		}
		if (!ft_strcmp(env_temp->key, "OLDPWD", ft_strlen(env_temp->key), ft_strlen("OLDPWD")))
		{
			free(env_temp->value);
			env_temp->value = oldpwd;
		}
		env_temp = env_temp->next;
	}
}

int	custom_cd(t_info *info, char **optarg)
{
	if (optarg[1])
		return (perror_cd_many("minishell", "cd"));
	if (chdir(optarg[0]) == -1)
		return (perror_cd("minishell", optarg[0]));
	else
		change_env(info);
	return (0);
}
