#include "../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;
	size_t	i;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	i = 0;
	ft_memset(ret, 0, count * size);
	return (ret);
}

void	*ft_alert_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (ret == NULL)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
	return (ret);
}