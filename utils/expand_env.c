#include "../include/minishell.h"

char	*expand_env(char *str, t_list *env_list)
{
	char	*ret;
	char	*str_slice;
	char	*env_value;
	char 	*exit_status = "exit_status";
	char	*key;
	char	*dlr_pos;

	ret = NULL;
	while (*str)
	{
		dlr_pos = ft_strchr(str, '$');
		if (!dlr_pos)
			break ;
		str_slice = ft_substr(str, 0, dlr_pos - str);
		ret = ft_strjoin(ret, str_slice);
		str = dlr_pos + 1;
		if (*str == '?')
			env_value = ft_strdup(exit_status); // 실제는 exit status itoa 해야함
		else if (is_valid_key_first(*str))
		{
			while (is_valid_key_last(*str))
				str++;
			key = ft_substr(dlr_pos + 1, 0, str - dlr_pos - 1);
			env_value = ft_strdup(find_value_in_env(key, env_list));
		}
		else
			env_value = ft_strdup("$");
		ret = ft_strjoin(ret, env_value);
	}
	return (ret);
}
