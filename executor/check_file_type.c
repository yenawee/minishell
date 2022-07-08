/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:54:51 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/08 17:03:05 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_ftype(char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat))
		return (FT_NOTFOUND);
	if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
		return (FT_DIR);
	return (FT_FILE);
}
