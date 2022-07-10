/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:56 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 18:12:13 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_redir(char *file_name, int flag, int target_fd, int mode)
{
	int	fd;

	if (mode)
		fd = open(file_name, flag, mode);
	else
		fd = open(file_name, flag);
	if (fd == -1)
		return (FAIL);
	if (dup2(fd, target_fd) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "dup2 fail\n");
	if (close(fd))
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "close fail\n");
	return (SUCCESS);
}

int	redir_in(char *file_name)
{
	return (_redir(file_name, O_RDONLY, STDIN_FILENO, 0));
}

int	redir_out(char *file_name)
{
	return (_redir(file_name, O_WRONLY | O_TRUNC | O_CREAT, \
					STDOUT_FILENO, 0644));
}

int	redir_append(char *file_name)
{
	return (_redir(file_name, O_WRONLY | O_APPEND | O_CREAT, \
					STDOUT_FILENO, 0644));
}

int	redir_heredoc(t_sh *sh)
{
	char		file_name[12];
	const char	*alnum = "0123456789abcdef";

	ft_strlcpy(file_name, "./heredoc_", 12);
	file_name[10] = alnum[(sh->heredoc_index)++];
	file_name[11] = '\0';
	return (_redir(file_name, O_RDONLY, STDIN_FILENO, 0));
}
