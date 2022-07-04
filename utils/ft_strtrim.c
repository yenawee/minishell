#include "../include/minishell.h"

static int	set_check(char c, char const *set)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (c == set[index])
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*rst;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	end = len;
	while (set_check(s1[start], set) && s1[start])
		start++;
	while (set_check(s1[end - 1], set) && s1[end - 1] && end > start)
		end--;
	rst = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!rst)
		return (NULL);
	len = ft_strlcpy(rst, s1 + start, end - start + 1);
	return (rst);
}
