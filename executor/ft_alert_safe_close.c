#include "../include/minishell.h"

void ft_alert_safe_close(int *fd)
{
	if (*fd != -1)
	{
		// printf("try close fd: %d\n", *fd);
		if (close(*fd))
			exit_msg(EXIT_FAILURE, STDERR_FILENO, "fail close()\n");
		*fd = -1;
	}
}