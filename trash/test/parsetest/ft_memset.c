#include "test.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	uc;
	size_t			i;

	ptr = (unsigned char *)b;
	uc = (unsigned char)c;
	i = 0;
	while (i++ < len)
		*ptr++ = uc;
	return (b);
}
