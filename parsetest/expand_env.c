#include "test.h"

int	is_valid_key_first(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_key_last(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*expand_env(char *str, t_list *env_list)
{
	int		start;
	int		end;
	char	*ret;
	char	*str_slice;
	char	*env_value;
	char 	*exit_status = "exit_status";
	char	*key;

	start = 0;
	end = 0;
	ret = NULL;
	while (str[end])
	{
		while (str[end] && str[end] != '$')
			end++;
		str_slice = ft_substr(str, start, end - start);
		ret = ft_strjoin(ret, str_slice);
		if (!str[end])
			break ;
		end++;
		start = end;
		if (str[end] == '?')
			env_value = ft_strdup(exit_status); // 실제는 exit status itoa 해야함
		else if (is_valid_key_first(str[end]))
		{
			while (is_valid_key_last(str[end]))
				end++;
			key = ft_substr(str, start, end - start);
			env_value = ft_strdup(find_value_in_env(key, env_list));
			start = end;
		}
		else
			env_value = ft_strdup("$");
		ret = ft_strjoin(ret, env_value);
	}
	return (ret);
}
