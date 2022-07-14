/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:43:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/14 10:51:46 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	_alert_getcwd(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (*pwd == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail getcwd()\n");
}

int	ft_pwd(void)
{
	char	*path;

	_alert_getcwd(&path);
	ft_putstr_fd(STDOUT_FILENO, path);
	ft_putstr_fd(STDOUT_FILENO, "\n");
	safe_free((void **)&path);
	return (EXIT_SUCCESS);
}
