#include "../include/minishell.h"

static char	*expand_until_quote(int *end, \
int start, char *str, t_list *env_list)
{
	char	*str_slice;

	while (str[*end] && str[*end] != '\'' && str[*end] != '\"')
			(*end)++;
	str_slice = ft_substr(str, start, *end - start);
	if (ft_strchr(str_slice, '$'))
		str_slice = expand_env(str_slice, env_list);
	return (str_slice);
}

static char	*expand_quotes(int c, char *s, t_list *env_list)
{
	char	*str_quote_trim;
	char	*tmp;

	if (c == '\'')
		str_quote_trim = ft_strtrim(s, "\'");
	if (c == '\"')
	{
		str_quote_trim = ft_strtrim(s, "\"");
		tmp = str_quote_trim;
		if (ft_strchr(str_quote_trim, '$'))
		{
			str_quote_trim = expand_env(str_quote_trim, env_list);
			safe_free(&tmp);
		}
	}
	return (str_quote_trim);
}

static char	*slice_str_between_quotes(int *start, \
int *end, char *str, t_list *env_list)
{
	char	*str_slice;
	char	*tmp;

	*start = (*end)++;
	while (str[*end] && str[*end] != str[*start])
		(*end)++;
	str_slice = ft_substr(str, *start, *end - *start + 1);
	tmp = str_slice;
	str_slice = expand_quotes(str[*start], str_slice, env_list);
	safe_free(&tmp);
	return (str_slice);
}

char	*expand_str(char *str, t_list *env_list)
{
	int		start;
	int		end;
	char	*str_slice;
	char	*ret;
	char	*tmp;

	ret = NULL;
	end = 0;
	start = 0;
	while (str[end])
	{
		str_slice = expand_until_quote(&end, start, str, env_list);
		ft_safe_strjoin(&ret, str_slice);
		if (!str[end])
			break ;
		safe_free(&str_slice);
		str_slice = slice_str_between_quotes(&start, &end, str, env_list);
		ft_safe_strjoin(&ret, str_slice);
		start = ++end;
	}
	return (ret);
}
