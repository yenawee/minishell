/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:05:49 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/11 16:38:39 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_msg(int exit_status, int fd, char *msg)
{
	ft_putstr_fd(fd, msg);
	exit(exit_status);
}

void	exit_command_perror_msg(int exit_status, char *cmd, char *msg)
{
	const char	*project_name = "minishell";

	ft_putstr_fd(STDERR_FILENO, project_name);
	ft_putstr_fd(STDERR_FILENO, ": ");
	ft_putstr_fd(STDERR_FILENO, cmd);
	ft_putstr_fd(STDERR_FILENO, ": ");
	ft_putstr_fd(STDERR_FILENO, msg);
	ft_putstr_fd(STDERR_FILENO, "\n");
	exit(exit_status);
}
