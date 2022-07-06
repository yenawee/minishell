#include "../include/minishell.h"

void	addtoken(t_token **list, char *begin, char *end, t_list *env_list)
{
	t_token	*new_node;
	t_token	*tmp;
	int		i;
	char	*str;

	new_node = ft_alert_calloc(1, sizeof(t_token));
	tmp = *list;
	str = ft_alert_calloc(end - begin + 2, sizeof(char));
	i = -1;
	while (++i < end - begin + 1)
		str[i] = begin[i];
	str[i] = '\0';
	new_node->str = str;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}
