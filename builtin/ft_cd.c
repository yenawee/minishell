/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenawee <yenawee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:26:57 by yenawee           #+#    #+#             */
/*   Updated: 2022/07/10 19:34:43 by yenawee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_target(char *str, t_list *env_list)
{
	char	*target;

	if (!ft_strcmp(str, "~") || !ft_strcmp(str, "~/"))
		target = get_env_value(env_list, "HOME");
	else if (!ft_strcmp(str, "-"))
		target = get_env_value(env_list, "OLDPWD");
	else
		target = ft_strdup(str);
	return (target);
}

int	ft_cd(t_list *env_list, char **argv)
{
	char	*oldpwd;
	char	*target;
	char	*cwd;

	oldpwd = getcwd(NULL, 0);
	target = get_target(argv[1], env_list);
	if (!target)
		return (EXIT_FAILURE);
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
