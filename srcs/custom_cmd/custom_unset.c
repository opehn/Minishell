#include "custom_cmd.h"
#include "error.h"

#include <stdio.h>

extern int g_exit_status;

int chk_unset_err(char **opts_arr)
{
	int	i;

	i = 0;
    if (opts_arr[0][0] == '-') //if option
    {
        ft_putendl_fd("minishell : unset : no option", STDERR_FILENO);
        g_exit_status = 0;
        return (1);
    }
	while (opts_arr[i]) //if args has space or =
	{
		if (ft_strchr(opts_arr[i], ' ') || ft_strchr(opts_arr[i], '='))
		{
			ft_putstr_fd("minishell : unset : ", STDERR_FILENO);
			ft_putstr_fd(opts_arr[0], STDERR_FILENO);
			ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
			g_exit_status = 1;
			return (1);
		}
		i++;
	}
    return (0);
}

int	unset_env(t_info *info, char **opts_arr)
{
	int		i;
	char	*key;
	t_env_list	*temp;
	t_env_list	*prev;

	i = 0;
	while(opts_arr[i])
	{
		key = opts_arr[i];
		temp = info->env_list;
		prev = temp;
		while(temp)
		{
			if(!ft_strcmp(temp->key, key, ft_strlen(temp->key), ft_strlen(key)))
			{
				prev->next = temp->next;
				free(temp);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return (0);
}

int	custom_unset(t_info *info, char **opts_arr)
{
	chk_unset_err(opts_arr);
	unset_env(info, opts_arr);
	return (0);
}

