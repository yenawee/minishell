#include "test.h"

char	*ft_strdup(const char *s1)
{
	char	*rst;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	rst = malloc(len * sizeof(char) + 1);
	if (!rst)
		return (NULL);
	while (s1[i])
	{
		rst[i] = s1[i];
		i++;
	}
	rst[i] = '\0';
	return (rst);
}
