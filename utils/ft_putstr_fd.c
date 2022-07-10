/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:06:26 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 20:06:27 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(int fd, char *msg)
{
	size_t	size;
	size_t	n;

	size = ft_strlen(msg);
	while (size)
	{
		n = write(fd, msg, size);
		msg += n;
		size -= n;
	}
}
