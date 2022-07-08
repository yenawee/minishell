#include "../include/minishell.h"

void ft_alert_safe_dup2(t_sh *sh, int fd, int to_fd)
{
	if (fd >= 0 && to_fd >= 0 && dup2(fd, to_fd) == -1)
		exit_msg(EXIT_FAILURE, sh->fd_stderr, "☎️fail dup2()\n");
	// ft_putstr_fd(sh->fd_stdout, "📨dup2 finish\n");
}