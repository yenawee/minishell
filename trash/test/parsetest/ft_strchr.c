#include "test.h"

char	*ft_strchr(const char *s, int c)
{
	char	*rst;

	rst = (char *)s;
	while (*rst != (char)c && *rst)
		rst++;
	if (*rst)
		return (rst);
	if (!(*rst) && (char)c == 0)
		return (rst);
	else
		return (NULL);
}
