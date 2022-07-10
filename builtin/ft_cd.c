#include "../include/minishell.h"

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;

	oldpwd = getcwd(NULL, 0);
	if (!ft_strcmp(argv[1], "~"))
	{
		target = get_env_value(env_list, "HOME");
		if (!target)
			return (EXIT_FAILURE);
	}
	else if (!ft_strcmp(argv[1], "-"))
	{
		target = get_env_value(env_list, "OLDPWD");
		if (!target)
			return (EXIT_FAILURE);
	}
	else
		target = argv[1];
	if (chdir(target) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: ");
		ft_putstr_fd(STDERR_FILENO, strerror(errno));
		ft_putstr_fd(STDERR_FILENO, "\n");
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	ft_export_one(&env_list, "PWD", cwd, 0);
	if (oldpwd)
		ft_export_one(&env_list, "OLDPWD", oldpwd, 0);
	return (EXIT_SUCCESS);
}
