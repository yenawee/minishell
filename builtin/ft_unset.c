#include "../include/minishell.h"

static void ft_del(void *p)
{
	t_env	*content;

	content = (t_env *)p;
	if (content)
	{
		safe_free((void **)&(content->key));
		safe_free((void **)&(content->value));
		free(content);
	}
}

static void ft_lst_remove_if(t_list **list, char *key)
{
	t_list 	*curr;
	t_env	*temp;
	t_list	*tmp;

	curr = *list;
	while (curr)
	{
		temp = (t_env *)curr->content;
		if (!ft_strcmp((const char *)temp->key, (const char *)key))
		{
			if (curr == *list)
				*list = curr->next;
			else
				tmp->next = curr->next;
			ft_lstdelone(curr, ft_del);
            return ;
		}
		tmp = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_list **list, char **argv)
{
	char	**keys;

	keys = ++argv;
	while (*keys)
	{
		ft_lst_remove_if(list, *keys);
		keys++;
	}
	return (EXIT_SUCCESS);
}
