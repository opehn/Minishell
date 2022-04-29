/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: acho <marvin@42.fr>						+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/28 23:34:04 by acho			  #+#	#+#			 */
/*   Updated: 2022/04/28 23:44:48 by acho             ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "free_data.h"
#include "error.h"
#include "action.h"

void	delete_info(t_info *info)
{
	if (info->root)
	{
		free(info->root);
		info->root = NULL;
	}
	if (info->heredoc)
	{
		free(info->heredoc);
		info->heredoc = NULL;
	}
}

void	free_forest(t_forest *forest)
{
	t_tree	*right_tree;

	while (forest->root)
	{
		right_tree = forest->root->right_child;
		free(forest->root->left_child->data);
		free(forest->root->left_child);
		free(forest->root->data);
		free(forest->root);
		if (right_tree && (right_tree->type == OPTARG))
		{
			if (right_tree->data)
				free(right_tree->data);
			free(right_tree);
			free(forest);
			return ;
		}
		forest->root = right_tree;
	}
}

void	free_red_data(char *data, char **red_data, char *red)
{
	if (data)
		free (data);
	if (red_data)
		free (red_data);
	if (red)
		free (red);
}

void	free_env_list(t_env_list *cur)
{
	free(cur->key);
	cur->key = NULL;
	free(cur->value);
	cur->value = NULL;
	free(cur);
	cur = NULL;
}

void	free_pipe(t_pipe_list *pipe)
{
	t_pipe_list	*next;

	while(pipe)
	{
		next = pipe->next;
		free(pipe->pipe_data);
		free(pipe);
		pipe = next;
	}
}
