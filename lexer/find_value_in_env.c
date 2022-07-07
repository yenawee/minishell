#include "../include/minishell.h"

char	*find_value_in_env(char *key, t_list *env_list)
{
	char	*s;
	t_list	*cur;

	cur = env_list;
	while (cur)
	{
		s = ((t_env *)cur->content)->key;
		if (!ft_strcmp(s, key))
			return (((t_env *)cur->content)->value);
		cur = cur->next;
	}
	return ("");
}
