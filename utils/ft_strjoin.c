#include "../include/minishell.h"

void	ft_safe_strjoin(char **ret, char *str)
{
	char	*tmp;

	tmp = *ret;
	*ret = ft_strjoin(*ret, str);
	safe_free(&tmp);
}

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

char	*ft_alert_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_alert_strdup(s2));
	if (!s2)
		return (ft_alert_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!rst)
		exit_msg(EXIT_FAILURE, STDERR_FILENO, "malloc error\n");
	ft_strlcpy(rst, s1, s1_len + 1);
	ft_strlcpy(rst + s1_len, s2, s2_len + 1);
	return (rst);
}

void	ft_alert_str_append(char **prev, char *added)
{
	char	*ret;
	char	*origin;
	size_t	size;

	if (*prev == NULL && added == NULL)
		ret = ft_alert_strdup("");
	else
		ret = ft_alert_strjoin((char const *)*prev, (char const *)added);
	if (*prev)
		free(*prev);
	*prev = ret;
}
