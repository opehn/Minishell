/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:45:42 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/24 16:07:53 by acho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error.h"
#include "env.h"
#include <stdbool.h>
#include <stdio.h>

t_pipe_list	*init_pipe_list(void)
{
	t_pipe_list	*new;

	new = malloc(sizeof(t_pipe_list));
	if (!new)
		exit_error(ERR_MALLOC);
	new->s_idx = 0;
	new->l_idx = 0;
	new->pipe_data = NULL;
	new->next = NULL;
	return (new);
}

void	append_pipe_list(t_pipe_list *cur, int l_idx)
{
	t_pipe_list *new;
	
	new = init_pipe_list();
	if (!new)
		exit_error(ERR_MALLOC); 
	new->s_idx = l_idx + 1;
	new->l_idx = l_idx;
	cur->next = new;
}

t_env_list 	*new_env_list(char *arg, char *equal)
{
	t_env_list *new;
	char	*argend;

	argend = arg;
	while(*argend)
		argend++;
	new = (t_env_list *)malloc(sizeof(t_env_list));
    if (!new)
        exit_error(ERR_MALLOC);
	new->key = ft_strndup(arg, (equal - arg));
    new->value = ft_strndup(equal + 1, argend - equal);
	new->next = NULL;
	return (new);
}

void	append_env_list(t_env_list *env_list, char *arg, char *equal)
{
	while (env_list)
		env_list = env_list->next;
	env_list = new_env_list(arg, equal);
	printf("key : %s, value : %s\n", env_list->key, env_list->value);
}
