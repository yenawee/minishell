#include "../include/minishell.h"

char	*get_env_value(t_list *env_list, char *key)
{
	t_list *curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strcmp(((t_env *)curr->content)->key, key))
			return (ft_strdup(((t_env *)curr->content)->value));
		curr = curr->next;
	}
	return (NULL);
}

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;

	oldpwd = getcwd(NULL, 0);
	if (argv[1] == '~/////////')
	{
		target = get_env_value(env_list, "HOME");
		if (!target)
			return (EXIT_FAILURE);
	}
	else if (argv[1] == '-')
	{
		target = get_env_value(env_list, "OLDPwD");
		if (!target)
			return (EXIT_FAILURE);
	}
	else
		target = argv[1];
	if (chdir(target) == -1)
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	ft_export_one(&env_list, "PWD", cwd, 0);
	if (oldpwd)
		ft_export_one(&env_list, "OLDPWD", oldpwd, 0);
	return (EXIT_SUCCESS);

}
