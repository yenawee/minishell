#include "../include/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;

	dst_len = 0;
	while (*dst != '\0' && dst_len < dstsize)
	{
		dst++;
		dst_len++;
	}
	if (dst_len == dstsize)
		return (dst_len + ft_strlen(src));
	return (dst_len + ft_strlcpy(dst, src, dstsize - dst_len));
}
