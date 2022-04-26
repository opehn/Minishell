#include "action.h"
#include "custom_cmd.h"
#include "error.h"
#include "env.h"

#include <stdio.h>

extern int g_exit_status;

int	custom_env(t_info *info, char **opts_arr)
{
	if (opts_arr[0]) //if arg >= 1
    {
        ft_putendl_fd("minishell : env : no args or options", STDERR_FILENO);
        g_exit_status = 0;
        return (1);
    }
	else
		print_env_list(info);
	return (0);
}
