#include "action.h"
#include "custom_cmd.h"
#include "error.h"

#include <stdio.h>

int	chk_export_error(char **opts_arr)
{
	if (opts_arr[0])
	{
		if (opts_arr[0][0] == '-')
			ft_putendl_fd("minishell : export : no option", STDERR_FILENO);
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
		ft_putendl_fd(env_list->value, STDOUT_FILENO);
		env_list = env_list->next;
	}
}

int	custom_export(t_info *info, char **opts_arr)
{
	if (chk_export_error(opts_arr))
		return (1);
	print_env_list(info);
	return (0);
}

