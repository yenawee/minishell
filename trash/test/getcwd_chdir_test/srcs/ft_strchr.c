/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:40:46 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/06/27 17:15:21 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	*s;
	unsigned char	uc;

	s = (unsigned char *)str;
	uc = (unsigned char)c;
	while (1)
	{
		if (*s == uc)
			return ((char *)s);
		if (!*s)
			return (0);
		s++;
	}
}
