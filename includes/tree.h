/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:17:25 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/12 21:43:47 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <fcntl.h>

typedef enum s_type
{
	INPUT_RED = 1,
	OUTPUT_RED = 2,
	APPEND_RED = 3,
	HEREDOC = 4,
	CMD = 5,
	OPTARG = 6,
	BRANCH = 7,
} t_type;

typedef struct s_tree
{
	int				type;
	char			*data;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
}	t_tree;

typedef struct s_forest
{
	int				fd[2];
	int				prefd;
	int				status;
	pid_t			pid;
	t_tree			*root;
	struct s_forest	*next;
} t_forest;

t_tree	*init_tree(int type, char *data, t_tree *left_child, t_tree *right_child);
void	delete_tree(t_tree *tree);

#endif