#include "../include/minishell.h"


char	*find_value_in_env(char *key, t_list *env_list)
{
	while (env_list)
	{
		char *s = ((t_env *)env_list->content)->key;
		if (!ft_strcmp(s, key))
			return (((t_env *)env_list->content)->value);
		env_list = env_list->next;
	}
	return ("");
}
