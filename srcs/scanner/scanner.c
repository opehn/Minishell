/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: taeheoki <taeheoki@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/26 14:14:51 by acho			  #+#	#+#			 */
/*   Updated: 2022/05/02 17:30:38 by acho             ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "scanner.h"
#include "error.h"
#include "parsing.h"

void	isequal(t_env_list *env_list, int *key_len)
{
	if (ft_strchr(env_list->key, '='))
		*key_len = ft_strlen(env_list->key) - 1;
	else
		*key_len = ft_strlen(env_list->key);
}

int	scan_token(t_tree *root, t_env_list *env_list)
{
	int		res;
	int		i;
	char	**remain;

	if (!root->data)
		return (0);
	remain = (char **) malloc(sizeof(char *) * 1);
	if (!remain)
		exit_error(ERR_MALLOC);
	init_str(remain);
	i = 0;
	res = 0;
	ignore_space(root->data, &i);
	res = iterate_scan(remain, &i, root, env_list);
	free(*remain);
	free(remain);
	return (res);
}

int	iterate_scan(char **remain, int *i, t_tree *root, t_env_list *env_list)
{
	int		flag;
	int		res;
	char	*data;

	res = 0;
	data = ft_strndup(root->data, ft_strlen(root->data));
	while (data[*i] && !res)
	{
		flag = *i;
		res = if_quot(data, i, remain);
		if (res)
			return (res);
		res = if_red(data, i, root, env_list);
		if (res)
			return (res);
		if (flag == *i)
		{
			append_char(data, remain, i);
			ignore_space(data, i);
			append_seperater(data, remain, i);
		}
	}
	free(data);
	grow_cmd(*remain, root, env_list);
	return (res);
}
