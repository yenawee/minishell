#include "../include/minishell.h"

void 	ft_env(t_list *list)
{
	t_list *curr;
	t_env	*temp;

	curr = list;
	while (curr)
	{
		temp = (t_env *)curr->content;
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		curr = curr->next;
	}
}
