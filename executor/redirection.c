/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:59:56 by hyeonjan          #+#    #+#             */
/*   Updated: 2022/07/12 13:40:51 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_read_and_expand(t_sh *sh, int file_fd, int pipe_fd)
{
	char	*str;
	char	buf[1024];
	int		res;

	ft_memset(buf, 0, 1024);
	str = NULL;
	while (42)
	{
		res = read(file_fd, buf, 1023);
		if (res == -1)
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail read()\n");
		buf[res] = '\0';
		if (res == 0)
			break ;
		ft_alert_str_append(&str, buf);
	}
	if (str)
		expand_in_heredoc(str, pipe_fd, sh->env_list);
	safe_free((void **)&str);
}

int	redir_heredoc(t_sh *sh)
{
	int			heredoc_pipe[2];
	char		file_name[11];
	int			heredoc_file_fd;

	ft_strlcpy(file_name, ".heredoc_0", 11);
	file_name[9] = "0123456789abcdef"[(sh->heredoc_index)++];
	heredoc_file_fd = open(file_name, O_RDONLY);
	if (heredoc_file_fd < 0)
		return (FAIL);
	if (pipe(heredoc_pipe) == -1)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail pipe()\n");
	_read_and_expand(sh, heredoc_file_fd, heredoc_pipe[WRITE]);
	ft_alert_safe_dup2(sh, heredoc_pipe[READ], STDIN_FILENO);
	ft_alert_safe_close(&heredoc_file_fd);
	ft_alert_safe_close(&heredoc_pipe[WRITE]);
	ft_alert_safe_close(&heredoc_pipe[READ]);
	return (SUCCESS);
}
