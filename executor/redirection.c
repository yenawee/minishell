/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjan <hyeonjan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:56 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/10 20:26:37 by hyeonjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_read_and_expand(t_sh *sh, int file_fd, int pipe_fd)
{
	char	*str;
	char	*new_str;
	char	buf[1024];
	int		res;

	buf[0] = '\0';
	str = NULL;
	new_str = NULL;
	while (42)
	{
		res = read(file_fd, buf, 1024);
		if (res == -1)
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail read()\n");
		if (res == 0)
			break ;
		new_str = ft_strjoin((const char *)str, (const char *)buf);
		safe_free((void **)&str);
		str = new_str;
		new_str = NULL;
	}
	expand_in_heredoc(str, pipe_fd, sh->env_list);
	safe_free((void **)str);
}

int	redir_heredoc(t_sh *sh)
{
	int			heredoc_pipe[2];
	char		file_name[12];
	int			fd;
	char		*str;

	ft_strlcpy(file_name, "./heredoc_0", 12);
	file_name[10] = "0123456789abcdef"[(sh->heredoc_index)++];
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (FAIL);
	if (pipe(heredoc_pipe) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail pipe()\n");
	str = NULL;
	_read_and_expand(sh, fd, heredoc_pipe[WRITE]);
	ft_alert_safe_dup2(sh, heredoc_pipe[READ], STDIN_FILENO);
	ft_alert_safe_close(&heredoc_pipe[WRITE]);
	ft_alert_safe_close(&heredoc_pipe[READ]);
	return (SUCCESS);
}
