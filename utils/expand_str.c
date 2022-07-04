#include "../include/minishell.h"

char *expand_str(char *str, t_list *env_list)
{
	int		start;
	int		end;
	char	*str_slice;
	char	*ret;
	char	*str_quote_trim;

	ret = NULL;
	end = 0;
	start = 0;
	while (str[end])
	{
		while (str[end] && str[end] != '\'' && str[end] != '\"')
			end++;
		str_slice = ft_substr(str, start, end - start);
		if (ft_strchr(str_slice, '$'))
			str_slice = expand_env(str_slice, env_list);
		ret = ft_strjoin(ret, str_slice);
		if (!str[end])
			break ;

		start = end;
		end++;
		while (str[end] && str[end] != str[start])
			end++;
		str_slice = ft_substr(str, start, end - start + 1);

		if (str[start] == '\'')
		{
			str_quote_trim = ft_strtrim(str_slice, "\'");
			ret = ft_strjoin(ret, str_quote_trim);
		}

		if (str[start] == '\"')
		{
			str_quote_trim = ft_strtrim(str_slice, "\"");
			if (ft_strchr(str_quote_trim, '$'))
				str_quote_trim = expand_env(str_quote_trim, env_list);
			ret = ft_strjoin(ret, str_quote_trim);
		}
		end++;
		start = end;
	}
	return (ret);
}
