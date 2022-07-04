#include "../include/minishell.h"

void	ft_putstr_fd(int fd, char *msg)
{
	size_t	size;
	size_t	n;

	size = ft_strlen(msg);
	while (size)
	{
		n = write(1, msg, size);
		msg += n;
		size -= n;
	}
}
