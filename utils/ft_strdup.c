/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:06:40 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:06:40 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*rst;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	rst = malloc(len * sizeof(char) + 1);
	if (!rst)
		return (NULL);
	while (s1[i])
	{
		rst[i] = s1[i];
		i++;
	}
	rst[i] = '\0';
	return (rst);
}

char	*ft_alert_strdup(const char *s1)
{
	char	*ret;

	ret = ft_strdup(s1);
	if (ret == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error");
	return (ret);
}
