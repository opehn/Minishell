/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:15:27 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 23:17:07 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "custom_cmd.h"

char	*get_env_value(t_env_list *env_list, char *key)
{
	t_env_list	*env_temp;

	env_temp = env_list;
	while (env_temp)
	{
		if (!ft_strcmp(env_temp->key, key, ft_strlen(env_temp->key), \
			ft_strlen(key)))
			return (ft_strdup(env_temp->value));
		env_temp = env_temp->next;
	}
	return (NULL);
}

t_env_list	*update_env(t_env_list *env_temp, char *pwd, \
						char *oldpwd, int *flag)
{
	if (!ft_strcmp(env_temp->key, "PWD", ft_strlen(env_temp->key), \
		ft_strlen("PWD")))
	{
		free(env_temp->value);
		env_temp->value = pwd;
	}
	if (!ft_strcmp(env_temp->key, "OLDPWD", ft_strlen(env_temp->key), \
		ft_strlen("OLDPWD")))
	{
		free(env_temp->value);
		env_temp->value = oldpwd;
		*flag = 1;
	}
	env_temp = env_temp->next;
	return (env_temp);
}

void	change_env(t_info *info)
{
	char		*pwd;
	char		*oldpwd;
	int			flag;
	t_env_list	*env_temp;

	flag = 0;
	env_temp = info->env_list;
	pwd = getcwd(NULL, 0);
	oldpwd = get_env_value(info->env_list, "PWD");
	while (env_temp)
		env_temp = update_env(env_temp, pwd, oldpwd, &flag);
	if (flag == 0)
		append_env_list(info, "OLDPWD", oldpwd);
}

int	custom_cd(t_info *info, char **optarg)
{
	if (!optarg || !(*optarg))
		return (2);
	else if (optarg[1])
		return (perror_cd_many("minishell", "cd"));
	else if (chdir(optarg[0]) == -1)
		return (perror_cd("minishell", optarg[0]));
	else
		change_env(info);
	return (0);
}
