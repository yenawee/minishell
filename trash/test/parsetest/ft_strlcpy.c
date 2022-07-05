#include "test.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	while (src[j] && (i < dstsize - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len);
}
