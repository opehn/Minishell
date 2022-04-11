/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:17:25 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/11 15:40:09 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef enum s_type
{
	RED = 0,
	CMD = 1,
	OPTARG = 2,
	BRANCH = 3,
} t_type;

typedef struct s_tree
{
	int				type;
	char			*data;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
}	t_tree;

t_tree	*init_tree(int type, char *data, t_tree *left_child, t_tree *right_child);
void	delete_tree(t_tree *tree);

#endif