/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:06:31 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:06:31 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	*rst;

	rst = (char *)s;
	while (*rst != (char)c && *rst)
		rst++;
	if (*rst)
		return (rst);
	if (!(*rst) && (char)c == 0)
		return (rst);
	else
		return (NULL);
}
