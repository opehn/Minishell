/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ch_no.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeheoki < taeheoki@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:56:51 by acho              #+#    #+#             */
/*   Updated: 2022/04/28 17:15:03 by taeheoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_ch_no(char *s, char c)
{
	char	*new_string;
	int		len;
	int		i;

	len = ft_strlen(s);
	new_string = (char *)malloc(len + 2);
	if (!new_string)
		return (0);
	i = 0;
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = c;
	new_string[i + 1] = '\0';
	return (new_string);
}
