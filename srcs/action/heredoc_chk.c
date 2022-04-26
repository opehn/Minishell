/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/26 18:10:01 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "scanner.h"
#include "prompt.h"

extern int	g_exit_status;

int	heredoc_cnt(t_forest *forest)
{
	int		i;
	t_tree	*temp;

	i = 0;
	temp = forest->root;
	while (forest->root->left_child)
	{
		if (forest->root->left_child->type == HEREDOC)
			++i;
		forest->root = forest->root->right_child;
	}
	forest->root = temp;
	return (i);
}

char	*line_expand(t_info *info, char *line)
{
	char	*temp;
	int		len;
	int		*i;

	len = ft_strlen(line);
	i = (int *)malloc(sizeof(int));
	temp = (char *)malloc(sizeof(char));
	*i = 0;
	temp[0] = 0;
	while (*i < len)
	{
		if (line[*i] == '$')
		{
			(*i)++;
			no_quot_expand(line, i, &temp, info->env_list);
		}
		temp = ft_strjoin_ch(temp, line[*i]);
		(*i)++;
	}
	free(line);
	line = 0;
	return (temp);
}

void	init_heredoc_buf(t_info *info, char *end_word, int index)
{
	char	*line;

	info->heredoc[index].index = index;
	while (1)
	{
		line = prompt_readline("> ");
		if (line != NULL && ft_strcmp(line, end_word, ft_strlen(line), \
			ft_strlen(end_word)))
		{
			line = line_expand(info, line);
			ft_putendl_fd(line, info->heredoc[index].fd[IN]);
			free(line);
			line = 0;
		}
		else
			break ;
	}
	if (line)
	{
		free(line);
		line = 0;
	}
}

int	heredoc_setting(t_info *info, t_forest	*cur_forest, int index)
{
	pipe(info->heredoc[index].fd);
	init_heredoc_buf(info, cur_forest->root->left_child->data, \
					index);
	close(info->heredoc[index].fd[IN]);
	index++;
	return (index);
}

void	heredoc_chk(t_info *info)
{
	t_forest	*cur_forest;
	t_tree		*temp;
	int			cnt;
	int			index;

	cur_forest = info->forest;
	cnt = heredoc_cnt(cur_forest);
	if (cnt == 0)
		return ;
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * cnt);
	temp = info->forest->root;
	index = 0;
	while (cur_forest)
	{
		while (cur_forest->root && cur_forest->root->left_child)
		{
			if (cur_forest->root->left_child->type == HEREDOC)
				index = heredoc_setting(info, cur_forest, index);
			cur_forest->root = cur_forest->root->right_child;
		}
		cur_forest = cur_forest->next;
	}
	info->forest->root = temp;
}
