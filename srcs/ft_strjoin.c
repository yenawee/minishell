/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 10:11:22 by ywee              #+#    #+#             */
/*   Updated: 2022/06/27 17:14:35 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!rst)
		return (NULL);
	ft_strlcpy(rst, s1, s1_len + 1);
	ft_strlcpy(rst + s1_len, s2, s2_len + 1);
	return (rst);
}
