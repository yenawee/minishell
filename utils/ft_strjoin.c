#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!rst)
		return (NULL);
	ft_strlcpy(rst, s1, s1_len + 1);
	ft_strlcpy(rst + s1_len, s2, s2_len + 1);
	return (rst);
}
