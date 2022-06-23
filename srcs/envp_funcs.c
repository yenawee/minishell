#include "minishell.h"

t_list	*envp_init(char **envp)
{
	t_list	*env_list;//8byte
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

void 	ft_env(t_list *list)
{
	t_list *curr;
	t_env	*temp;

	curr = list;
	while (curr)
	{
		temp = (t_env *)curr->content;
		printf("%s=%s\n", temp->key, temp->value);
		curr = curr->next;
	}
}

void	ft_del(void *p)
{
	t_env	*content;

	content = (t_env *)p;
	if (content)
	{
		ft_safe_free((void **)&content->key);
		ft_safe_free((void **)&content->value);
		free(content);
	}
}

void	ft_lst_remove_if(t_list **list, char *key)
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
		}
		tmp = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_list **list, char **keys)
{
	while (*keys)
		ft_lst_remove_if(list, *keys++);
}

int main(int argc, char **argv, char **envp)
{
	t_list *env_list;

	env_list = envp_init(envp);
	char	**keys = malloc(sizeof(void *) * 2);
	keys[0] = "a";
	keys[1] =  NULL;
	ft_unset(&env_list, keys);
	ft_env(env_list);
	return 0;
}