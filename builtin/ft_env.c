#include "../include/minishell.h"

int	ft_env(t_list *list)
{
	t_list	*curr;
	t_env	*temp;

	curr = list;
	while (curr)
	{
		temp = (t_env *)curr->content;
		if (temp->value)
		{
			ft_putstr_fd(STDOUT_FILENO, temp->key);
			ft_putstr_fd(STDOUT_FILENO, "=");
			ft_putstr_fd(STDOUT_FILENO, temp->value);
			ft_putstr_fd(STDOUT_FILENO, "\n");
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
