/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:06:14 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:06:14 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, count * size);
	return (ret);
}

void	*ft_alert_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (ret == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
	return (ret);
}
