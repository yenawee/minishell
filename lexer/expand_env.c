#include "../include/minishell.h"

static char	*expand_env_if(char **str, t_list *env_list, char *dlr_pos)
{
	char	*exit_status = "exit_status";
	char	*env_value;
	char	*key;

	if (**str == '?')
		env_value = ft_strdup(exit_status); // 실제는 exit status itoa 해야함
	else if (is_valid_key_first(**str))
	{
		while (is_valid_key_last(**str))
			(*str)++;
		key = ft_substr(dlr_pos + 1, 0, *str - dlr_pos - 1);
		env_value = ft_strdup(find_value_in_env(key, env_list));
		safe_free(&key);
	}
	else
		env_value = ft_strdup("$");
	return (env_value);
}

void	ft_safe_strjoin(char **ret, char *str)
{
	char	*tmp;

	tmp = *ret;
	*ret = ft_strjoin(*ret, str);
	safe_free(&tmp);
}

char	*expand_env(char *str, t_list *env_list)
{
	char	*ret;
	char	*str_slice;
	char	*env_value;
	char	*dlr_pos;

	ret = NULL;
	while (*str)
	{
		dlr_pos = ft_strchr(str, '$');
		if (!dlr_pos)
		{
			ft_safe_strjoin(&ret, str);
			break ;
		}
		str_slice = ft_substr(str, 0, dlr_pos - str);
		ft_safe_strjoin(&ret, str_slice);
		str = dlr_pos + 1;
		env_value = expand_env_if(&str, env_list, dlr_pos);
		ft_safe_strjoin(&ret, env_value);
	}
	return (ret);
}
