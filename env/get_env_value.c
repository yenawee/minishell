#include "../include/minishell.h"

char	*get_env_value(t_list *env_list, char *key)
{
	t_list	*curr;
	char	*ret;

	curr = env_list;
	ret = NULL;
	while (curr)
	{
		if (!ft_strcmp(((t_env *)curr->content)->key, key))
        {
			//printf("%s\n", ((t_env *)curr->content)->value);
            ret = ft_strdup(((t_env *)curr->content)->value);
			return (ret);
        }
        //printf("key : %s, value : %s\n", ((t_env *)curr->content)->key, ((t_env *)curr->content)->value);
        curr = curr->next;
	}
	return (ret);
}
