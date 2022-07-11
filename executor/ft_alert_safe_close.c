/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alert_safe_close.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:42:02 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/11 20:42:23 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_alert_safe_close(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd))
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail close()\n");
		*fd = -1;
	}
}
