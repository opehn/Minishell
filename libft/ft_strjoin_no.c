/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:56:51 by acho              #+#    #+#             */
/*   Updated: 2022/04/28 17:15:20 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_no(char *s1, char *s2)
{
	char	*new_string;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(len + 1);
	if (!new_string)
		return (0);
	ft_strlcpy(new_string, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_string, s2, len + 1);
	return (new_string);
}
