/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:26 by taeheoki          #+#    #+#             */
/*   Updated: 2022/04/18 18:44:56 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wifexited(int status)
{
	return ((status & 0177) == 0);
}

int	ft_wifsignaled(int status)
{
	return ((status & 0177) != 0);
}

int	ft_wexitstatus(int status)
{
	return (((status >> 8) & 0x000000ff) % 128);
}

int	ft_wtermsig(int status)
{
	return ((status & 0177) + 128);
}