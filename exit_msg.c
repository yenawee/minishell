#include "minishell.h"

void	exit_msg(int exit_status, int fd, char msg)
{
	ft_putstr_fd(fd, msg);
	exit(exit_status);
}
