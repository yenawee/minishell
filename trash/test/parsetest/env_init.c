#include "test.h"

t_list	*envp_init(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	t_env	*content;
	char	*s;

	env_list = NULL;
	while (*envp)
	{
		s = ft_strchr(*envp, '=');
		*s = '\0';
		content = malloc(sizeof(t_env));
		content->key = ft_strdup(*envp);
		content->value = ft_strdup(s + 1);
		new_node = ft_lstnew(content);
		ft_lstadd_back(&env_list, new_node);
		envp++;
	}
	return (env_list);
}
