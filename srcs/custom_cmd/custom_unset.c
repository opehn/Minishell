#include "custom_cmd.h"
#include "error.h"

#include <stdio.h>

int	cnt_arr_len(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		printf("envp[%d] : %s\n", i, envp[i]);
		i++;
	}
	return (i);
}

int	custom_unset(t_info *info, char **opts_arr)
{
	int	arr_len;

	arr_len = cnt_arr_len(info->envp);

	return (0);
}

