/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:17:25 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/10 14:26:15 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_tree
{
	char			*data;
	struct s_tree	left_child;
	struct s_tree	right_child;
}	t_tree;

#endif