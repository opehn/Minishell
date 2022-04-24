#include "action.h"
#include "custom_cmd.h"
#include "error.h"
#include "env.h"

#include <stdio.h>

extern int g_exit_status;

char	*find_equal(char *arg)
{
	while(*arg)
	{
		if (*arg == '=')
			return (arg);
		arg++;
	}
	return (NULL);
}

int	chk_export_error(char **opts_arr)
{
	if (opts_arr[0][0] == '-') //if option
	{
		ft_putendl_fd("minishell : export : no option", STDERR_FILENO);
		g_exit_status = 0;
		return (1);
	}
	if (opts_arr[1]) //if arg > 1
	{
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

void	print_env_list(t_info *info)
{
	t_env_list *env_list;

	env_list = info->env_list;
	while(env_list)
	{
		write(STDOUT_FILENO, env_list->key, ft_strlen(env_list->key));
		write(STDOUT_FILENO, "=", 1);
		ft_putendl_fd(env_list->value, STDOUT_FILENO);
		env_list = env_list->next;
	}
}

int	custom_export(t_info *info, char **opts_arr)
{
	char	*equal;

	if (!opts_arr[0])
	{
		print_env_list(info);
		return (0);
	}
	if (chk_export_error(opts_arr))
		return (1);
	else
	{
		equal = find_equal(opts_arr[0]);
		if (!equal)
		{
			g_exit_status = 0;
			return (1);
		}
		append_env_list(info->env_list, opts_arr[0], equal);
	}
	return (0);
}
