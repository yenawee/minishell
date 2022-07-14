/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:53:46 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/14 09:45:09 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_space(int fd, char *space)
{
	char	*buf;
	char	*tmp;
	int		read_size;

	buf = (char *)malloc(sizeof(char) * 21);
	if (!buf)
		return (NULL);
	read_size = read(fd, buf, 20);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		tmp = space;
		space = ft_alert_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(space, '\n') || !space)
			break ;
		read_size = read(fd, buf, 20);
	}
	free(buf);
	buf = NULL;
	if (read_size < 0)
		return (NULL);
	return (space);
}

char	*get_printline(char *space)
{
	char	*line;
	int		i;
	int		newline_i;

	i = 0;
	newline_i = 0;
	while (space[newline_i] && space[newline_i] != '\n')
		newline_i++;
	line = (char *)malloc(sizeof(char) * newline_i + 2);
	if (!line)
		return (NULL);
	while (i <= newline_i)
	{
		line[i] = space[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*space;
	char		*line;
	char		*tmp;

	if (fd < 0)
		return (NULL);
	space = get_space(fd, space);
	if (!space)
		return (NULL);
	if (!(*space))
	{
		free(space);
		space = NULL;
		return (NULL);
	}
	line = get_printline(space);
	tmp = space;
	space = ft_alert_strdup(tmp + ft_strlen(line));
	free(tmp);
	tmp = NULL;
	if (!space)
		return (NULL);
	return (line);
}
