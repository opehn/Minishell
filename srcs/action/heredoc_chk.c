/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 20:32:33 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/21 01:13:50 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "scanner.h"
#include "prompt.h"

int	heredoc_cnt(t_forest *forest)
{
	int	i;

	i = 0;
	while (forest)
	{
		while (forest->root)
		{
			if (forest->root->left_child->type == HEREDOC)
				++i;
			forest->root = forest->root->right_child;
		}
		forest = forest->next;
	}
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
		if (line[*i] == '&')
			no_quot_expand(line, i, &temp, info->env_list);
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
		line = readline("> ");
		if (line != NULL && ft_strcmp(line, end_word))
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

void	heredoc_chk(t_info *info)
{
	t_forest	*cur_forest;
	int			cnt;
	int			index;

	cur_forest = info->forest;
	cnt = heredoc_cnt(cur_forest);
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * cnt);
	info->heredoc->fd[IN] = 0;
	info->heredoc->fd[OUT] = 0;
	index = 0;
	while (cur_forest)
	{
		while (cur_forest->root)
		{
			if (cur_forest->root->left_child->type == HEREDOC)
			{
				pipe(info->heredoc[index].fd);
				init_heredoc_buf(info, cur_forest->root->left_child->data, index);
				close(info->heredoc[index].fd[IN]);
				index++;
			}
			cur_forest->root = cur_forest->root->right_child;
		}
		cur_forest = cur_forest->next;
	}
}