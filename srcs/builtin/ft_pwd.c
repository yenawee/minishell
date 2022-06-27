/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:43:09 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/06/27 23:43:16 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		exit(EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
}
