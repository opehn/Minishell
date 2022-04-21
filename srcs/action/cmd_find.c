#include "action.h"
#include <stdio.h>

int	find_cmd(t_env_list *env_list, char *cmd)
{
	char *path;
	char	**cmd_array;

	path = NULL;

	path = make_path(env_list, cmd);
	cmd_array = ft_split(path, ':');
	int i = 0;
	while (cmd_array[i])
	{
		printf("cmd_array[%d] : %s\n", i, cmd_array[i]);
		i++;
	}
	/*find_cmd();
	if (find_cmd())
		execve();
	else
		return (ERR_CMD);*/
	

	return (0);

}

char	*make_path(t_env_list *env_list, char *cmd)
{
	char *path;

	path = malloc(1);
	path[0] = '\0';
	while(env_list)
	{
		if(!ft_strcmp(env_list->key, "PATH"))
			path = ft_strndup(env_list->value, ft_strlen(env_list->value));
		env_list = env_list->next;
	}

	return (path);
}
