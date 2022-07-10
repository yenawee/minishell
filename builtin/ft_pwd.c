/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:43:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 16:59:14 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd(STDOUT_FILENO, path);
	ft_putstr_fd(STDOUT_FILENO, "\n");
	safe_free(&path);
	return (EXIT_SUCCESS);
}
