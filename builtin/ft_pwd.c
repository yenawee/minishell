/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywee <ywee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:43:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/04 20:59:38 by ywee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
