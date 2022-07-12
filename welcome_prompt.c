/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 23:08:10 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/12 17:21:52 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	welcome_prompt(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("wallpaper", O_RDONLY);
	i = 0;
	if (fd < 0)
		return ;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i < 8)
			printf("\e[36;36m%s\e[0m", line);
		else
			printf("%s", line);
		i++;
		free(line);
	}
	close(fd);
}
