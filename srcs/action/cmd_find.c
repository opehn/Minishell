#include "action.h"
#include <stdio.h>
#include <dirent.h>

int	no_fork_cmd(char *cmd)
{ 
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (!ft_strcmp(cmd, "cd", cmd_len, 2))
		return (CMD_CD);
	if (!ft_strcmp(cmd, "export", cmd_len, 6))
		return (CMD_EXPORT);
	if (!ft_strcmp(cmd, "unset", cmd_len, 5))
		return (CMD_UNSET);
	if (!ft_strcmp(cmd, "exit", cmd_len, 4))
		return (CMD_EXIT);
	return (0);
}

int	find_custom_cmd(char *cmd)
{ 
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (!ft_strcmp(cmd, "echo", cmd_len, 4))
		return (CMD_ECHO);
	if (!ft_strcmp(cmd, "cd", cmd_len, 2))
		return (CMD_CD);
	if (!ft_strcmp(cmd, "pwd", cmd_len, 3))
		return (CMD_PWD);
	if (!ft_strcmp(cmd, "export", cmd_len, 6))
		return (CMD_EXPORT);
	if (!ft_strcmp(cmd, "unset", cmd_len, 5))
		return (CMD_UNSET);
	if (!ft_strcmp(cmd, "exit", cmd_len, 4))
		return (CMD_EXIT);
	return (0);
}

char	*find_builtin_cmd(t_env_list *env_list, char *cmd)
{
	char	*path;
	char	**path_array;

	path = find_env_path(env_list);
	path_array = ft_split(path, ':');
	return (match_builtin_cmd(path_array, cmd));
}

char	*match_builtin_cmd(char **path_array, char *cmd)
{
	DIR				*cur_dir;
	struct dirent	*cur_dir_info;
	int				i;

	i = 0;
	while (path_array[i])
	{
		cur_dir = opendir(path_array[i]);
		cur_dir_info = readdir(cur_dir);
		while (cur_dir_info != NULL)
		{
			if (!ft_strcmp(cmd,cur_dir_info->d_name, ft_strlen(cmd), ft_strlen(cur_dir_info->d_name)))
			{
				path_array[i] = ft_strjoin_ch(path_array[i], '/');
				return (ft_strjoin(path_array[i], cmd));
			}
			cur_dir_info = readdir(cur_dir);
		}
		i++;
	}
	return (NULL);

}

char	*find_env_path(t_env_list *env_list)
{
	char *path;

	path = malloc(1);
	path[0] = '\0';
	while(env_list)
	{
		if(!ft_strcmp(env_list->key, "PATH", ft_strlen(env_list->key), 4))
			path = ft_strndup(env_list->value, ft_strlen(env_list->value));
		env_list = env_list->next;
	}
	return (path);
}
