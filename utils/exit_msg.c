#include "../include/minishell.h"

void	exit_msg(int exit_status, int fd, char *msg)
{
	ft_putstr_fd(fd, msg);
	exit(exit_status);
}

void	exit_command_perror_msg(int exit_status, char *cmd, char *msg)
{
	const char	*project_name = "minishell";

	ft_putstr_fd(project_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(exit_status);
}