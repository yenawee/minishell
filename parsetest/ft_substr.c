#include "test.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rst;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!(*s) || start >= s_len || len == 0)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (!rst)
		return (NULL);
	ft_strlcpy(rst, s + start, len + 1);
	return (rst);
}
