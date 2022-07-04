#include "../include/minishell.h"

void	ft_del(void *p)
{
	t_env	*content;

	content = (t_env *)p;
	if (content)
	{
		safe_free((void **)&content->key);
		safe_free((void **)&content->value);
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

int	ft_unset(t_list **list, char **keys)
{
	while (*keys)
		ft_lst_remove_if(list, *keys++);
	return (EXIT_SUCCESS);
}

void	ft_export_one(t_list **list, char *key, char *value, int plus_flag)
{
	t_list	*curr;
	t_env	*tmp;
	t_env	*content;
	t_list	*new_node;
	char	*temp;
	curr = *list;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp((const char *)tmp->key, (const char *)key))
		{
			if (plus_flag)
			{
				temp = tmp->value;
				tmp->value = ft_strjoin(temp, value);
				free(temp);
			}
			else
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		curr = curr->next;
	}
	content = malloc(sizeof(t_env));
	content->key = ft_strdup(key);
	if (value)
		content->value = ft_strdup(value);
	else
		content->value = NULL;
	new_node = ft_lstnew(content);
	ft_lstadd_back(list, new_node);
}

static int	check_valid_key(char *key)
{
	int	len;

	len = ft_strlen(key);
	if (is_valid_key_first(key[0]) && is_valid_key_last(key[len - 1]))
		return (TRUE);
	return (FALSE);
}


int	ft_export(t_list **list, char **str)
{
	char	*key;
	char	*value;
	char	*s;
	int		plus_flag;
	char	*p;

	plus_flag = 0;
	while (*str)
	{
		s = ft_strchr(*str, '=');
		if (!s)
		{
			if (check_valid_key(*str))
				ft_export_one(list, *str, NULL, plus_flag);
			else
				printf("not a valid identifier\n");
		}
		else
		{
			p = ft_strchr(*str, '+');
			if (p + 1 == s)
			{
				plus_flag = 1;
				*p = '\0';
			}
			*s = '\0';
			key = *str;
			value = s + 1;
			if (check_valid_key(key))
				ft_export_one(list, key, value, plus_flag);
			else
				printf("not a valid identifier\n");
		}
		str++;
	}
	return (EXIT_SUCCESS);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_list *env_list;

// 	env_list = envp_init(envp);
// 	char	**keys = malloc(sizeof(void *) * 3);
// 	keys[0] = ft_strdup("a");
// 	keys[1] =  ft_strdup("b=222");
// 	keys[2] = NULL;
// 	ft_export(&env_list, keys);
// 	ft_export_no_arg(env_list);
// 	// ft_unset(&env_list, keys);
// 	// ft_env(env_list);
// 	return 0;
// }
