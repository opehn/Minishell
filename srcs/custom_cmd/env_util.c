/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: taeheoki <taeheoki@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/30 16:07:18 by acho			  #+#	#+#			 */
/*   Updated: 2022/05/02 11:45:24 by acho             ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "custom_cmd.h"
#include <stdio.h>

t_env_list	*new_env_list(char *key, char *value)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		exit_error(ERR_MALLOC);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	append_env_list(t_info *info, char *key, char *value)
{
	t_env_list	*temp;

	temp = info->env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env_list(key, value);
}

void	modify_env_list(t_info *info, char **key_value, int key_index)
{
	int			i;
	t_env_list	*temp;
	t_env_list	*old;
	t_env_list	*new;
	t_env_list	*next;

	i = 0;
	temp = info->env_list;
	while (i < key_index - 1)
	{
		temp = temp->next;
		i++;
	}
	old = temp->next;
	next = temp->next->next;
	new = new_env_list(key_value[0], key_value[1]);
	temp->next = new;
	new->next = next;
	free(old);
}

int	find_match_key(t_env_list *env_list, char *key)
{
	int	i;
	int	cur_key_len;
	int	list_key_len;

	i = 0;
	if (!ft_strchr(key, '='))
		cur_key_len = ft_strlen(key);
	else
		cur_key_len = ft_strlen(key) - 1;
	while (env_list)
	{
		if (!ft_strchr(env_list->key, '='))
			list_key_len = ft_strlen(env_list->key);
		else
			list_key_len = ft_strlen(env_list->key) - 1;
		if (!ft_strcmp(env_list->key, key, list_key_len, cur_key_len))
			return (i);
		env_list = env_list->next;
		i++;
	}
	return (-1);
}

int	make_key_value(char *arg, char **key_value)
{
	char	*argend;
	char	*equal;

	equal = ft_strchr(arg, '=');
	argend = arg;
	while (*argend)
		argend++;
	if (!equal)
	{
		key_value[0] = ft_strndup(arg, argend - arg);
		key_value[1] = "\0";
	}
	else
	{
		key_value[0] = ft_strndup(arg, (equal - arg) + 1);
		key_value[1] = ft_strndup(equal + 1, argend - equal);
	}
	return (0);
}
