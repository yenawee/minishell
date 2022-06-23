#include "../../include/minishell.h"

void	ft_pwd(t_list	*env_list)
{
	t_list *curr;
	t_env	*tmp;

	curr = env_list;

	while (curr)
	{
		tmp = (t_env*)curr->content;
		if (!ft_strcmp(tmp->key, "PWD"))
		{	
			printf("%s\n", tmp->value);
			return ;
		}
		curr = curr->next;
	}
}

// int main(int ac, char **av, char **envp)
// {
// 	t_list *env_list = envp_init(envp);
// 	ft_pwd(env_list);

// 	return 0;
// }