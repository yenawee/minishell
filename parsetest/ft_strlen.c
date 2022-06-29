#include "test.h"

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}
